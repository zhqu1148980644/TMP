# -*- coding: utf-8 -*-
"""
Created on Mon Apr 29 15:45:03 2019

@author: zhong

Reference:
https://github.com/Hironsan/anago
https://github.com/kyzhouhzau/Sequence_Labeling
"""

import glob
import json
import math
import multiprocessing
import os
import pickle
import re
import time
import subprocess
import gensim
import nltk
import numpy as np
import pandas as pd
import tensorflow as tf
from keras import initializers, regularizers, constraints
from keras.callbacks import Callback
from keras.callbacks import ModelCheckpoint
from keras.layers import Dense, LSTM, Bidirectional, Embedding, Input, Dropout, TimeDistributed
from keras.layers import Concatenate
from keras.models import Model
from keras.preprocessing.sequence import pad_sequences
from keras.utils import plot_model, Sequence
from keras_contrib.layers import CRF
from nltk import PunktSentenceTokenizer, RegexpTokenizer
from nltk.tokenize.treebank import TreebankWordTokenizer
from seqeval.metrics import f1_score, classification_report
from sklearn.externals import joblib

from tensorflow.contrib import rnn
from tensorflow.contrib.layers.python.layers import initializers
from keras.utils.np_utils import to_categorical

tf.logging.set_verbosity(tf.logging.ERROR)
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'


################################################DEPRECATED CODE########################################################
# Tranform json file to BIO file with native scanning way. slow
def json_to_tab(input, output):
    outfile = open(output, "w", encoding='utf-8', newline='\n')
    for file in input:
        with open(file) as f:
            source = json.loads(f.read())
            text = source['text'].replace('\n', ' ')
            length = len(text)
            sent_span = list(sent_tokenizer.span_tokenize(text))
            token_span_sentence = [
                [(st + i, st + j)
                 for i, j in word_tokenizer.span_tokenize(text[st: ed])]
                for st, ed in sent_span
            ]
            pos_tags = [
                pos[1]
                for st, ed in sent_span
                for pos in nltk.pos_tag(word_tokenizer.tokenize(text[st: ed]))
            ]
            denotations = source["denotations"]
            # Guard.
            denotations.append({'obj': None, 'span': {'begin': length, 'end': length}})
            cur = 0
            token_index = 0
            for sentence in token_span_sentence:
                for token_start, token_end in sentence:
                    # Skip denotation which start is less than the former denotation's end.
                    if cur and cur != len(denotations):
                        last_end = denotations[cur - 1]['span']['end']
                        while denotations[cur]['span']['begin'] < last_end:
                            print("pass one denotation: ", file, cur)
                            cur += 1
                            if cur == len(denotations):
                                break
                    cur_denote = denotations[cur]
                    start = cur_denote['span']['begin']
                    end = cur_denote['span']['end']
                    entity = cur_denote['obj']
                    token = text[token_start: token_end]
                    pos = pos_tags[token_index]
                    token_index += 1
                    if token_end <= start:
                        write_row(outfile, token, pos, MARKER[0])
                    # e.g.  token: gain   denotation: 'gain-of-information'
                    elif token_start == start or (token_start - 1) == start:
                        write_row(outfile, token, pos, MARKER[1], entity)
                    else:
                        write_row(outfile, token, pos, MARKER[3], entity)
                    if token_end == end:
                        cur += 1
                outfile.write("\n")
        outfile.write("\n")
        print("Loading: ", file, " done.")
    outfile.close()


## for generating word2vec model based on your own corpus
class Sentence(object):
    def __init__(self, records):
        self.records = records

    def __iter__(self):
        for record in self.records:
            for sentence in record.tokens_by_sentence():
                yield sentence


def generate_wordvec(records, reuse=True):
    if not reuse or not os.path.exists(config.embedding_path):
        wordvec = gensim.models.Word2Vec(Sentence(records),
                                         size=config.embed_dim,
                                         window=10,
                                         min_count=0,
                                         workers=multiprocessing.cpu_count())

        wordvec.wv.save_word2vec_format(config.embedding_path, binary=True)


def get_embedding(id2word):
    print("Start fetching embedding table!")
    wordvec = gensim.models.KeyedVectors.load_word2vec_format(config.embedding_path, binary=True)
    embedding_table = []
    count = 0
    for i in range(len(id2word)):
        word = id2word[i]
        if word in wordvec:
            embedding_table.append(wordvec[word])
        else:
            if word.upper() in wordvec:
                embedding_table.append(wordvec[word.upper()])
            else:
                count += 1
                embedding_table.append(np.random.normal(0, 0.1, [config.embed_dim]))
    embedding_table = np.array(embedding_table, dtype=np.float32)
    print("{} words not exists in wordvec".format(count))
    print("Fetching embedding table done!")
    return embedding_table


def load_dict(data, reuse=True):
    """
    :data: pandas.Dataframe. should contain column: token entity sentence
    :return: tuple. (word2id, id2word, label2id, id2label)
    """
    if reuse and os.path.exists("dict.pkl"):
        with open("dict.pkl", 'rb') as f:
            word2id, id2word, label2id, id2label = pickle.load(f)
    else:
        word2id, id2word = {}, {}
        word2id['<PAD>'], id2word[0] = 0, '<PAD>'

        for i, word in enumerate(data['token'].unique(), 1):
            word2id[word] = i
            id2word[i] = word

        label2id, id2label = {}, {}
        label2id['<PAD>'], id2label[0] = 0, '<PAD>'
        for i, label in enumerate(data['entity'].unique(), 1):
            label2id[label] = i
            id2label[i] = label

        with open("dict.pkl", 'wb') as f:
            pickle.dump([word2id, id2word, label2id, id2label], f)

    return word2id, id2word, label2id, id2label


def _load_data(data, reuse_dict=True):
    """
    :data: pandas.Dataframe. should contain column: token entity sentence
    :return: tuple. (X, Y, seq_len). X,Y are padded with word <PAD>'s id.
    :return X: each row represent one sentence, each col in one row represent each words in this sentence.
    :return Y: each row represent one sentence, each col in one row represent each words' label in this sentence.
    :return seq_len: each sentence's actual word number.
    """
    word2id, id2word, label2id, id2label = load_dict(data, reuse_dict)
    max_len = config.max_len
    sentence_nums = len(data['sentence'].unique())
    data.loc[:, ['token']] = data['token'].apply(lambda word: word2id[word])
    data.loc[:, ['entity']] = data['entity'].apply(lambda label: label2id[label])
    X = np.zeros([sentence_nums, max_len], np.int32)
    Y = np.zeros([sentence_nums, max_len], np.int32)
    seq_len = []
    for i, sent in data.groupby("sentence"):
        length = len(sent) if len(sent) <= config.max_len else config.max_len
        X[i] = np.lib.pad(np.array(sent['token'])[:max_len],
                          [0, max_len - length],
                          'constant',
                          constant_values=(0, 0))
        Y[i] = np.lib.pad(np.array(sent['entity'])[:max_len],
                          [0, max_len - length],
                          'constant',
                          constant_values=(0, 0))
        seq_len.append(length)
    return X, Y, seq_len


######################################################Utils#############################################################
PATTERN = re.compile(r'''(?x)   # set flag to allow verbose regexps: ignores spaces and newlines
        (?:[A-Z]\.)+            # abbreviations, e.g. U.S.A.
        | \$?\d+(?:\.\d+)?%?    # currency and percentages, e.g. $12.40, 82%
        | '(?:s|nt)\b           # 's, 'nt
        #     | \w+(?:-\w+)*    # words with optional internal hyphens
        | [a-zA-Z0-9]+          # words without internal hyphens e.g. Type1_gene(Attention: \w contains _)
        | \.\.\.                # ellipsis
        | [.,;"?:]              # these are separate tokens
        | [][()_`\|\n-]+        # these tokens are grouped; includes ] and [ and -
        | [^a-zA-Z0-9_\s]       # find these character in the AGAC training data.
        ''')

# default tokenizer
word_tokenizer = RegexpTokenizer(PATTERN)
sent_tokenizer = PunktSentenceTokenizer()


class Text(object):
    """
    Abstract text. e.g a paragrah, abstract and an essay.
    """

    def __init__(self, text, s_tokenizer=sent_tokenizer, w_tokenizer=word_tokenizer):
        """
        :param text: str
        :param s_tokenizer: sentence_tokenzier
        :param w_tokenizer: word_tokenizer
        """
        self._text = text
        self._pos_tags = None
        self._sent_span = []
        self._token_span = []
        self._tokens = None
        self.st = s_tokenizer
        self.wt = w_tokenizer

    def __len__(self):
        return len(self._text)

    @property
    def text(self):
        return self._text

    def _generate_token_by_sentence(self):
        if self._tokens is None:
            self._tokens = [
                [token for token in self.wt.tokenize(sentence)]
                for sentence in self.sentences()
            ]

    def tokens_by_sentence(self):
        self._generate_token_by_sentence()

        return self._tokens

    def tokens(self):
        """
        :return type: Generator of all tokens.
        """
        self._generate_token_by_sentence()

        for tokens in self._tokens:
            for token in tokens:
                yield token

    def token_span(self):
        """
        :return type: Generator of all token spans. span : (start, end).
        """
        if not self._token_span:
            for span in self.wt.span_tokenize(self.text):
                yield span
                self._token_span.append(span)
        else:
            for span in self._token_span:
                yield span

    def sentences(self):
        """
        :return type: Generator of strings of each sentence fetched by sentence_span().
        """
        for st, ed in self.sentence_span():
            yield self.text[st: ed]

    def sentence_span(self):
        """
        :return type: Generator of all sentence spans. span : (start, end).
        """
        if not self._sent_span:
            for span in self.st.span_tokenize(self.text):
                yield span
                self._sent_span.append(span)
        else:
            for span in self._sent_span:
                yield span

    # time comsuming.
    def pos_tags(self):
        """
        :return type: List of part-of-speech tags. Each pos' position is in accordance
        with the position of each token fetched by token_span() or tokens()
        """
        if self._pos_tags is None:
            self._generate_token_by_sentence()
            self._pos_tags = [
                pos[1]
                for tokens_by_sentence in self._tokens
                for pos in nltk.pos_tag(tokens_by_sentence)
            ]
        return self._pos_tags


################################################Data processing from AGAC###############################################
class Relation(object):
    """
    Not implemented
    """

    def __init__(self, info, text):
        pass


class Denotation(object):
    """
    Used for feching begin, end, obj in a object-oriented way.
    """

    def __init__(self, info, text):
        self.info = info
        self.text = text

    @property
    def id(self):
        return self.info['id']

    @property
    def begin(self):
        return self.info['span']['begin']

    @property
    def end(self):
        return self.info['span']['end']

    @property
    def obj(self):
        return self.info['obj']

    def __repr__(self):
        return self.text[self.begin: self.end]

    def __str__(self):
        return repr(self.info)


class AGACRecord(Text):
    """
    Abstract AGACRecord.
    """

    def __init__(self, file, s_tokenizer=sent_tokenizer, w_tokenizer=word_tokenizer):
        """

        :param file:
        :param s_tokenizer:
        :param w_tokenizer:
        """
        file = file
        data = json.loads(open(file).read())
        super().__init__(data['text'].replace('\n', ' '), s_tokenizer, w_tokenizer)
        self._file = file
        self._data = data
        self._denotations = [Denotation(d, self.text) for d in self._data['denotations']]
        self._relations = [Relation(r, self.text) for r in self._data['relations']]
        self._deno_dict = {}

    def __repr__(self):
        return "<AGACRecord: {}>".format(self.id)

    @property
    def filename(self):
        return self._file

    @property
    def id(self):
        return self._data['sourceid']

    @property
    def denotations(self):
        return self._denotations

    @property
    def relations(self):
        return self._relations

    # Use hash table for quick seaching of denotations of each token. key is token + str(token_start).
    @property
    def deno_dict(self):
        """
        :return type: Dict. key: token + str(token_start)  value: entity  e.g. (B-Protein/I-Gene...)
        """
        if not self._deno_dict:
            for deno in self.denotations:
                word = self.text[deno.begin: deno.end]
                token_span = list(self.wt.span_tokenize(word))
                first = word[token_span[0][0]: token_span[0][1]] + str(deno.begin)
                # This step passes some denotation.Info can be stores in case needed.
                if first in self._deno_dict:
                    continue
                self._deno_dict[first] = 'B-' + deno.obj
                for i in range(1, len(token_span)):
                    self._deno_dict[word[token_span[i][0]: token_span[i][1]] \
                                    + str(deno.begin + token_span[i][0])] = 'I-' + deno.obj
        return self._deno_dict


class AGACTransform(object):

    def __init__(self, files):
        """

        :param files:
        """
        if len(files):
            if isinstance(files[0], str):
                self.records = [AGACRecord(file) for file in files]
            elif isinstance(files[0], AGACRecord):
                self.records = files
            else:
                raise ValueError("Receive list of filenames or object of AGACRecord")

    def split(self, ratio=0.7, shuffle=True):
        """
        :return: tuple: (AGACTransform(), AGACTransform())
        """
        if shuffle:
            self.records = np.random.permutation(self.records)
        length = int(len(self.records) * ratio)
        return AGACTransform(self.records[: length]), AGACTransform(self.records[length:])

    def write_bio(self, file, pos=False, filter=False, delimiter='\t'):
        """
        Extract token, entity, pos from the record object(AGACRecord).
        
        :file:   str.    The output filename of the BIO data.
        :pos:    bool.   Write the pos(part of speech) info in the second column if pos set to True.
        :filter: bool.   Only write tokens of sentence which contains at least one entity annotation.
        """
        # Write with the second column as pos info could take some time.
        if not pos:
            self._write_bio(self.records, file, filter, delimiter)
        else:
            self._write_bio_with_pos(self.records, file, filter, delimiter)

    @staticmethod
    def get_deno_span(record):
        """
        Fecth the sentence span with at least one entity annotations(denotaion).
        """
        sentence_with_deno = []
        index = 0
        for st, ed in record.sentence_span():
            for deno in record.denotations[index:]:
                if deno.begin >= st and deno.end <= ed:
                    sentence_with_deno.append((st, ed))
                    index += 1
                    break

        # function for cheking if a word span within any sentence span
        def check_skip(st, ed):
            for sent_begin, sent_end in sentence_with_deno:
                if st >= sent_begin and ed <= sent_end:
                    return False
            return True

        return check_skip

    def _write_bio(self, records, output, filter=False, delimiter='\t'):
        outfile = open(output, "w", encoding='utf-8', newline='\n')
        for record in records:
            text = record.text
            # Key is token+str(token_start) ; value is mark.
            deno_dict = record.deno_dict
            # find the empty sentence which has no denotations.
            if filter:
                check_skip = self.get_deno_span(record)
            for st, ed in record.token_span():
                # Skip the empty sentence which has no denotaions.
                if filter and check_skip(st, ed):
                    continue
                token = text[st: ed]
                marker = deno_dict.get(token + str(st), None)
                if marker is not None:
                    outfile.write("{0}{2}{1}\n".format(token, marker, delimiter))
                else:
                    outfile.write("{0}{1}O\n".format(token, delimiter))
                    if token in (".", "?", "!") and text[st + 1: st + 2] == ' ':
                        outfile.write('\n')

    # Write with the second column as pos info could take some time.
    def _write_bio_with_pos(self, records, output, filter=False, delimiter='\t'):
        outfile = open(output, "w", encoding='utf-8', newline='\n')
        for record in records:
            text = record.text
            # Key is token+str(token_start) ; value is mark(B-Gene/I-Protein...).
            deno_dict = record.deno_dict
            pos_tags = record.pos_tags()
            index = -1
            # find the empty sentence which has no denotations.
            if filter:
                check_skip = self.get_deno_span(record)
            for st, ed in record.token_span():
                index += 1
                # Skip the empty sentence which has no denotaions.
                if filter and check_skip(st, ed):
                    continue
                token = text[st: ed]
                marker = deno_dict.get(token + str(st), None)
                if marker is not None:
                    outfile.write("{0}{3}{1}{3}{2}\n".format(token, pos_tags[index], marker, delimiter))
                else:
                    outfile.write("{0}{2}{1}{2}O\n".format(token, pos_tags[index], delimiter))
                    if token in (".", "?", "!") and text[st + 1: st + 2] == ' ':
                        outfile.write('\n')

    def get_dataframe(self, file=None, pos=False, filter=False, delimiter='\t'):
        if file is not None:
            data = self.read_df_from_file(file, pos, delimiter)
        else:
            tokens, poss, entities, sentences = [], [], [], []
            sent_id = 0
            for record in self.records:
                text = record.text
                # Key is token+str(token_start) ; value is mark(B-Gene/I-Protein...).
                deno_dict = record.deno_dict
                if pos:
                    pos_tags = record.pos_tags()
                index = -1
                # find the empty sentence which has no denotations.
                if filter:
                    check_skip = self.get_deno_span(record)
                for st, ed in record.token_span():
                    index += 1
                    # Skip the empty sentence which has no denotaions.
                    if filter and check_skip(st, ed):
                        continue
                    token = text[st: ed]
                    tokens.append(token)
                    sentences.append(sent_id)
                    if pos:
                        poss.append(pos_tags[index])
                    marker = deno_dict.get(token + str(st), None)
                    if marker is not None:
                        entities.append(marker)
                    else:
                        entities.append('O')
                        if token in (".", "?", "!") and text[st + 1: st + 2] == ' ':
                            sent_id += 1
            if pos:
                data = pd.DataFrame(np.column_stack([tokens, poss, entities, sentences]),
                                    columns=['token', 'pos', 'entity', 'sentence'])
                data['sentence'] = data['sentence'].astype('int')
            else:
                data = pd.DataFrame(np.column_stack([tokens, entities, sentences]),
                                    columns=['token', 'entity', 'sentence'])
                data['sentence'] = data['sentence'].astype('int')

        return data

    @staticmethod
    def read_df_from_file(file, pos=False, delimiter='\t'):
        # set skip_bliank_lines to False will treat empty line as NAN row
        # set keep_default_na to False will not interpret words like 'null' 'None' as NAN
        data = pd.read_csv(file, header=None, delimiter=delimiter, skip_blank_lines=False, keep_default_na=False,
                           na_values='')
        try:
            sentence_ids = np.zeros([len(data)], dtype=np.int)
            last = 0
            sent_id = 0
            for index in data.index[data.isnull().any(axis=1)]:
                sentence_ids[last: index] = sent_id
                sent_id += 1
                last = index
            data['sentence'] = sentence_ids
            data = data.dropna(how='any')
            if pos:
                data.columns = ["token", "pos", "entity", "sentence"]
            else:
                data.columns = ["token", "entity", "sentence"]

        except Exception as e:
            raise ValueError("Your input file's format is wrong.\nerror:", e)

        return data


def write_text(records, output):
    """
    Simply write main info of all records in a single file.
    :records: list. list of AGACRecord. fetched from AGACTranform().records
    :output: str. filename of output file.
    """
    outfile = open(output, "w", encoding='utf-8', newline='\n')
    for record in records:
        outfile.write("#########################################\n")
        outfile.write(record.filename + '\n')
        outfile.write(record.text + '\n')
        for deno in record.denotations:
            outfile.write(str(deno))
            outfile.write('\n')
    outfile.close()


##########################################Processing data for model training############################################
def load_data(data, pos=False, delimiter='\t'):
    """
    :data: pandas.Dataframe. should contain column: token entity sentence
    :data: str. bio file is also supported
    """
    if isinstance(data, pd.DataFrame):
        data = data
    elif isinstance(data, str):
        data = AGACTransform.read_df_from_file(data, pos, delimiter)
    else:
        raise ValueError("data should be str or pd.dataframe")

    tokens, poss, Y = [], [], []
    for i, sent in data.groupby("sentence"):
        tokens.append(sent['token'].tolist())
        if pos:
            poss.append(sent['pos'].tolist())
        Y.append(sent['entity'].tolist())
    if pos:
        return (tokens, poss), Y
    else:
        return tokens, Y


def process(func):
    def inner(self, token):
        if self.lower:
            return func(self, token.lower())
        else:
            return func(self, token)

    return inner


class Vocabulary(object):
    def __init__(self, data=None, lower=False):
        """
        Just for test.
        :param data: currently only support pd.dataframe.
        :param lower: lower case
        """
        self.data = data
        self.lower = lower
        if self.data is not None:
            self._token2id = {'[PAD]': 0}
            self._id2token = {0: '[PAD]'}
            for id, token in enumerate(data, 1):
                self._token2id[token] = id
                self._id2token[id] = token

    def __len__(self):
        return len(self._token2id)

    @process
    def token2id(self, token):
        if self.data is not None:
            return self._token2id.get(token, 0)
        else:
            return 0

    def __getitem__(self, item):
        return self.token2id(item)

    def id2token(self, id):
        if self.data is not None:
            return self._id2token.get(id, '[PAD]')
        else:
            return '[PAD]'

    def get_embeddings(self, file, dim):
        if isinstance(file, str):
            try:
                word2vec = gensim.models.KeyedVectors.load_word2vec_format(file, binary=True)
            except Exception as e:
                word2vec = gensim.models.KeyedVectors.load_word2vec_format(file, binary=False)
        elif isinstance(file, dict):
            word2vec = file
        else:
            raise ValueError("load embedding file wrong")

        embeddings = np.zeros([len(self._token2id), dim])
        for word in self._token2id:
            if word in word2vec:
                embeddings[self._token2id[word]] = word2vec[word]

        return embeddings


class Table(object):
    def __init__(self, lower=False):
        self.init = False
        self.lower = lower
        self.token_vocab = None
        self.char_vocab = None
        self.pos_vocab = None
        self.label_vocab = None

    @property
    def table_size(self):
        if self.init:
            return [len(vocab) if vocab is not None else None for vocab in
                    (self.token_vocab, self.char_vocab, self.pos_vocab, self.label_vocab)]
        else:
            return None, None, None, None

    def fit(self, data, char=False, pos=False):
        tokens = data['token'].unique()
        self.token_vocab = Vocabulary(tokens)
        if char:
            self.char_vocab = Vocabulary(np.unique([char for token in tokens for char in token]), self.lower)
        else:
            self.char_vocab = Vocabulary(lower=self.lower)
        if pos:
            self.pos_vocab = Vocabulary(data['pos'].unique(), self.lower)
        else:
            self.pos_vocab = Vocabulary(lower=self.lower)
        self.label_vocab = Vocabulary(data['entity'].unique(), self.lower)
        self.init = True

        return self

    def transform(self, X, Y):
        try:
            if isinstance(X, tuple):
                token_list, pos_list = X[0], X[1]
            else:
                token_list, pos_list = X, None
            tokens = [[self.token_vocab.token2id(word) for word in sent] for sent in token_list]
            token_ids = self.padding_zero(tokens)
            chars = [[[self.char_vocab[char] for char in word] for word in sent] for sent in token_list]
            char_ids = self.padding_zero(chars, nested=True)
            inputs = [token_ids, char_ids]
            if pos_list is not None:
                pos = [[self.pos_vocab.token2id(word) for word in sent] for sent in pos_list]
                pos_ids = self.padding_zero(pos)
                inputs.append(pos_ids)
            if Y:
                label_ids = self.padding_zero([[self.label_vocab.token2id(word) for word in sent] for sent in Y])
                label_ids_matrix = to_categorical(label_ids, num_classes=len(self.label_vocab)).astype(int)
                if len(label_ids_matrix.shape) == 3:
                    label_ids_matrix = label_ids_matrix
                else:
                    np.expand_dims(label_ids_matrix, axis=0)

                return inputs, label_ids_matrix
            else:
                return inputs
        except Exception as e:
            print(e)
            raise ValueError("Please fit the table first.")

    def reverse(self, X, Y):
        """
        Wait for implementation.
        :param X:
        :param Y:
        :return:
        """
        pass

    def reverse_labelid(self, Y, lengths=None):
        """Return label strings.
        Args:
            y: label id matrix.
            lengths: sentences length.
        Returns:
            list: list of list of strings.
        """
        Y = np.argmax(Y, -1)
        inverse_y = [[self.label_vocab.id2token(id) for id in ids] for ids in Y]
        if lengths is not None:
            inverse_y = [iy[:l] for iy, l in zip(inverse_y, lengths)]

        return inverse_y

    def get_word_embeddings(self, file, dim):
        if self.init:
            return self.token_vocab.get_embeddings(file, dim)
        else:
            raise ValueError("Please fit the table first.")

    @staticmethod
    def padding_zero(sequences, nested=False):
        """
        Not tested. copied from anago.

        :param array: np.ndarray. supposed to be 2-dimensional if nested set to False else 3-dimensional
        :param nested: bool. 3-dimensional
        :return: np.ndarray
        """
        if not nested:
            return pad_sequences(sequences, padding='post')
        else:
            max_sent_len = 0
            max_word_len = 0
            for sent in sequences:
                max_sent_len = max(len(sent), max_sent_len)
                for word in sent:
                    max_word_len = max(len(word), max_word_len)

            x = np.zeros((len(sequences), max_sent_len, max_word_len)).astype('int32')
            for i, sent in enumerate(sequences):
                for j, word in enumerate(sent):
                    x[i, j, :len(word)] = word

            return x

    def save(self, filepath):
        joblib.dump(self, filepath)

    @staticmethod
    def load(filepath):
        return joblib.load(filepath)


class BatchData(Sequence):
    def __init__(self, X, Y, table, batch_size=32, shuffle=False):
        self.table = table
        self.X = X
        self.Y = Y
        self.batch_size = batch_size
        self.shuffle = shuffle
        if isinstance(self.X, tuple):
            self.batch_step = math.ceil(len(self.X[0]) / self.batch_size)
        else:
            self.batch_step = math.ceil(len(self.X) / self.batch_size)

    def __getitem__(self, index):
        if isinstance(self.X, tuple):
            batch_x = (self.X[0][index * self.batch_size: (index + 1) * self.batch_size],
                       self.X[1][index * self.batch_size: (index + 1) * self.batch_size])
        else:
            batch_x = self.X[index * self.batch_size: (index + 1) * self.batch_size]
        batch_y = self.Y[index * self.batch_size: (index + 1) * self.batch_size]

        return self.table.transform(batch_x, batch_y)

    def on_epoch_end(self):
        if self.shuffle:
            pass

    def __len__(self):
        return self.batch_step


#######################################################Model############################################################


class config(object):
    batch_size = 32
    epoch = 50
    embed_dim = 200
    max_len = 140
    position_dim = 200
    sinusoid = True
    num_units = 200
    num_layer = 3
    cell = 'lstm'
    regulation = True
    nomalize = True
    embedding_mode = 'concat'
    embedding_scale = False  # in embedding step
    position_scale = False
    dropout_rate = 0.5
    keeprate = 0.8
    num_class = 26
    use_crf = True
    exponential_decay = False
    learning_rate = 0.0001
    log_dir = 'log_dir'
    embedding_path = 'vecmodel/pubmed.bin'


class F1score(Callback):

    def __init__(self, test, preprocessor=None):
        super(F1score, self).__init__()
        self.data = test
        self.p = preprocessor

    def get_lengths(self, y_true):
        lengths = []
        for y in np.argmax(y_true, -1):
            try:
                i = list(y).index(0)
            except ValueError:
                i = len(y)
            lengths.append(i)

        return lengths

    def on_epoch_end(self, epoch, logs={}):
        label_true = []
        label_pred = []

        for i in range(len(self.data)):
            x_true, y_true = self.data[i]

            lengths = self.get_lengths(y_true)
            y_pred = self.model.predict_on_batch(x_true)

            y_true = self.p.reverse_labelid(y_true, lengths)
            y_pred = self.p.reverse_labelid(y_pred, lengths)

            label_true.extend(y_true)
            label_pred.extend(y_pred)

        score = f1_score(label_true, label_pred)
        print(' - f1: {:04.2f}'.format(score * 100))
        print(classification_report(label_true, label_pred))
        logs['f1'] = score


class BiLSTMCRF(object):
    """A Keras implementation of BiLSTM-CRF for sequence labeling.

    References
    --
    Guillaume Lample, Miguel Ballesteros, Sandeep Subramanian, Kazuya Kawakami, Chris Dyer.
    "Neural Architectures for Named Entity Recognition". Proceedings of NAACL 2016.
    https://arxiv.org/abs/1603.01360
    """

    def __init__(self,
                 use_crf=True,
                 use_char=True,
                 use_pos=True,
                 max_len=100,
                 num_labels=None,
                 word_vocab_size=None,
                 char_vocab_size=None,
                 pos_vocab_size=None,
                 word_embedding_dim=100,
                 char_embedding_dim=25,
                 pos_embedding_dim=25,
                 num_layers=1,
                 lstm_size=100,
                 char_lstm_size=25,
                 pos_lstm_size=200,
                 dropout=0.5,
                 embeddings=None):
        """
        
        :param use_crf: 
        :param use_char: 
        :param use_pos: 
        :param max_len: 
        :param num_labels: 
        :param word_vocab_size: 
        :param char_vocab_size: 
        :param pos_vocab_size: 
        :param word_embedding_dim: 
        :param char_embedding_dim: 
        :param pos_embedding_dim: 
        :param num_layers: 
        :param lstm_size: 
        :param char_lstm_size: 
        :param pos_lstm_size: 
        :param dropout: 
        :param embeddings: 
        """
        super(BiLSTMCRF).__init__()
        self._use_crf = use_crf
        self._use_char = use_char
        self._use_pos = use_pos
        self._max_len = max_len
        self._num_labels = num_labels
        self._word_vocab_size = word_vocab_size
        self._char_vocab_size = char_vocab_size
        self._pos_vocab_size = pos_vocab_size
        self._word_embedding_dim = word_embedding_dim
        self._char_embedding_dim = char_embedding_dim
        self._pos_embedding_dim = pos_embedding_dim
        self._num_layers = num_layers
        self._lstm_size = lstm_size
        self._char_lstm_size = char_lstm_size
        self._pos_lstm_size = pos_lstm_size
        self._dropout = dropout
        self._embeddings = embeddings

    @staticmethod
    def multi_bilstm(input, lstm_size, layer, dropout=0.2):
        bilstm_layer = input
        for size in range(layer):
            bilstm_layer = Bidirectional(
                LSTM(lstm_size, return_sequences=True, recurrent_dropout=dropout))(bilstm_layer)
            # bilstm_layer = Dropout(dropout)(bilstm_layer)
        return bilstm_layer

    def build(self):
        # build word embedding
        word_ids = Input(batch_shape=(None, None), dtype='int32', name='word_input')

        inputs = [word_ids]
        # word embedding
        if self._embeddings is None:
            word_embeddings = Embedding(input_dim=self._word_vocab_size,
                                        output_dim=self._word_embedding_dim,
                                        mask_zero=True,
                                        name='word_embedding', )(word_ids)
        else:
            word_embeddings = Embedding(input_dim=self._embeddings.shape[0],
                                        output_dim=self._embeddings.shape[1],
                                        mask_zero=True,
                                        weights=[self._embeddings],
                                        name='word_embedding')(word_ids)
        embeddings = word_embeddings
        # character embedding
        if self._use_char:
            char_ids = Input(batch_shape=(None, None, None), dtype='int32', name='char_input')
            inputs.append(char_ids)
            char_embeddings = Embedding(input_dim=self._char_vocab_size,
                                        output_dim=self._char_embedding_dim,
                                        mask_zero=True,
                                        name='char_embedding')(char_ids)
            char_embeddings = TimeDistributed(Bidirectional(LSTM(self._char_lstm_size, recurrent_dropout=0.5)))(
                char_embeddings)
            embeddings = Concatenate()([embeddings, char_embeddings])
            embeddings = Dropout(self._dropout)(embeddings)

        # part of speech embedding
        if self._use_pos:
            pos_ids = Input(batch_shape=(None, None), dtype='int32', name='pos_input')
            inputs.append(pos_ids)
            pos_embeddings = Embedding(input_dim=self._pos_vocab_size,
                                       output_dim=self._pos_embedding_dim,
                                       mask_zero=True,
                                       name='pos_embedding')(pos_ids)
            # pos_embeddings = Bidirectional(LSTM(self._pos_lstm_size, return_sequences=True))(pos_embeddings)
            # pos_embeddings = self.multi_bilstm(pos_embeddings, self._lstm_size, self._num_layers, self._dropout)
            # pos_embeddings = Dropout(self._dropout)(pos_embeddings)
            embeddings = Concatenate()([embeddings, pos_embeddings])
            embeddings = Dropout(self._dropout)(embeddings)

        # multilayer bilstm
        z = self.multi_bilstm(embeddings, self._lstm_size, self._num_layers, self._dropout)
        z = Dense(self._max_len, activation='relu')(z)

        if self._use_crf:
            crf = CRF(self._num_labels, sparse_target=False)
            loss = crf.loss_function
            pred = crf(z)
        else:
            loss = 'categorical_crossentropy'
            pred = Dense(self._num_labels, activation='softmax')(z)

        model = Model(inputs=inputs, outputs=pred)

        return model, loss


def train_test(
        model,
        x_train,
        y_train,
        x_test=None,
        y_test=None,
        table=None,
        epochs=1,
        batch_size=32,
        verbose=1,
        callbacks=None,
        shuffle=True):
    """
    :param model:
    :param x_train:
    :param y_train:
    :param x_test:
    :param y_test:
    :param table:
    :param epochs:
    :param batch_size:
    :param verbose:
    :param callbacks:
    :param shuffle:
    :return:
    """

    train_seq = BatchData(x_train, y_train, table, batch_size, shuffle=True)

    if x_test and y_test:
        valid_seq = BatchData(x_test, y_test, table, batch_size)
        f1 = F1score(valid_seq, preprocessor=table)
        callbacks = [f1] + callbacks if callbacks else [f1]

    model.fit_generator(generator=train_seq,
                        epochs=epochs,
                        callbacks=callbacks,
                        verbose=verbose,
                        shuffle=shuffle,
                        )


def split_samples(files, ratio, shuffle=False):
    if shuffle:
        files = np.random.permutation(files)
    length = int(len(files) * ratio)
    return files[: length], files[length:]


def run_wapiti(train_file, test_file, pattern_file):
    train = subprocess.Popen('wapiti train -a sgd-l1 -t 15 -p {} {} train.mod'
                             .foramt(pattern_file, train_file), shell=True)
    train.wait()
    test = subprocess.Popen("wapiti label -c -m train.mod {} labeled_test.tab".format(test_file), shell=True)
    test.wait()
    eval = subprocess.Popen("conlleval.pl -d $'\t' <labeled_test.tab ", shell=True, stdout=subprocess.PIPE)
    print(eval.stdout.read())


if __name__ == "__main__":
    files = list(glob.iglob('AGAC_training/*json'))
    agac = AGACTransform(files)

    #    train with wapiti
    train, test = agac.split(ratio=0.85, shuffle=True)
    train.write_bio("train.tab", pos=False, filter=False)
    test.write_bio("test.tab", pos=False, filter=True)
    run_wapiti("train.tab", "test.tab", "pattern.txt")

    # train with bilstm+crf
    data = agac.get_dataframe(pos=True, filter=False)
    table = Table(lower=False).fit(data, char=True, pos=True)
    try:
        word_embedding = table.get_word_embeddings('vecmodel/pubmed.bin', 200)
    except Exception as e:
        print(e, "\nReading model file failuer.")
        word_embedding = None
    ts, cs, ps, ls = table.table_size
    model = BiLSTMCRF(
        use_crf=True,
        use_char=True,
        use_pos=True,
        max_len=150,
        num_labels=ls,
        word_vocab_size=ts,
        char_vocab_size=cs,
        pos_vocab_size=ps,
        word_embedding_dim=200,
        char_embedding_dim=25,
        pos_embedding_dim=25,
        num_layers=1,
        lstm_size=200,
        char_lstm_size=25,
        pos_lstm_size=50,
        dropout=0.5,
        embeddings=word_embedding)

    x_train, y_train = load_data(train.get_dataframe(pos=True, filter=False), pos=True)
    x_test, y_test = load_data(test.get_dataframe(pos=True, filter=True), pos=True)
    model, loss = model.build()
    model.compile(loss=loss, optimizer='adam')
    plot_model(model, to_file='bilstm_crf_model.png', show_shapes=True, show_layer_names=True)
    print(model.summary())
    train_test(model, x_train, y_train, x_test, y_test, table, batch_size=32, epochs=200)
    model.save("111", "222")
