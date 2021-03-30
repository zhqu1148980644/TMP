# !/usr/bin/python3
# -*- coding: utf-8 -*-
#altered version of Tetris game using PyQt5 http://zetcode.com/gui/pyqt5/tetris/
#Key is class Shape.coordsTable  ,by which we could know every shape's whole inforamtion
'''
The bottom line is we could calculate a specific shape's every square's cordinates (x,y,means the x'th row and y'th column)
from a center square's coordinates and it's coordsTable which contains other squares' relative coordinates
For example:
shape:SShape
center square:   (25,26)
other squares' coordsTable:((0, 0), (-1, 0), (-1, 1), (0, -1))
for each squares' coords:(newx,newy) = (25+x,25+y)
all squares' coordinates:(25,26),(24,26),(24,25),(25,25)
coordsTable = (
    ((0, 0), (0, 0), (0, 0), (0, 0)),
    ((0, 0), (0, 1), (-1, 0), (-1, -1)),
    ((0, 0), (-1, 0), (-1, 1), (0, -1)),
    ((0, 0), (0, 1), (0, 2), (0, -1)),
    ((0, 0), (-1, 0), (1, 0), (0, -1)),
    ((0, 0), (0, -1), (1, 0), (1, -1)),
    ((0, 0), (0, 1), (-1, 1), (0, -1)),
    ((0, 0), (0, 1), (1, 1), (0, -1))
)
Old version's coordsTable:
(newx,newy) = (25+x,25-y)
coordsTable = (
        ((0, 0),     (0, 0),     (0, 0),     (0, 0)),
        ((0, -1),    (0, 0),     (-1, 0),    (-1, 1)),
        ((0, -1),    (0, 0),     (1, 0),     (1, 1)),
        ((0, -1),    (0, 0),     (0, 1),     (0, 2)),
        ((-1, 0),    (0, 0),     (1, 0),     (0, 1)),
        ((0, 0),     (1, 0),     (0, 1),     (1, 1)),
        ((-1, -1),   (0, -1),    (0, 0),     (0, 1)),
        ((1, -1),    (0, -1),    (0, 0),     (0, 1))
    )
'''

from PyQt5.QtWidgets import QMainWindow, QFrame, QDesktopWidget, QApplication, QAction, qApp, QHBoxLayout
from PyQt5.QtWidgets import QLCDNumber, QVBoxLayout, QPushButton, QGridLayout, QWidget, QLabel, QMessageBox
from PyQt5.QtCore import Qt, QBasicTimer, pyqtSignal, QDateTime
from PyQt5.QtGui import QPainter, QColor, QIcon

import sys, random


class Main(QMainWindow):

    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):
        #initiates application UI#

        self.TetrisWidget = TetrisWidget(self)
        self.setCentralWidget(self.TetrisWidget)
        self.statusbar = self.statusBar()
        #change the statusbar following the signal of Tetris_board's msg2Statusbar
        self.TetrisWidget.tTritrisBoard.msg2Statusbar[str].connect(self.statusbar.showMessage)
        self.setWindowIcon(QIcon(r'C:\Users\zhong\Desktop\icon.jpg'))
        # setting menu bar
        menubar = self.menuBar()
        OptionMenu = menubar.addMenu('&Option')
        startAction = QAction(QIcon(r'C:\Users\zhong\Desktop\start.png'), '&Start', self)
        startAction.setStatusTip('Start the game !')
        startAction.setShortcut('Ctrl+O')
        startAction.triggered.connect(self.TetrisWidget.start)
        OptionMenu.addAction(startAction)
        StopAction = QAction(QIcon(r'C:\Users\zhong\Desktop\stop.png'), '&Stop', self)
        StopAction.setStatusTip('Stop the game !')
        StopAction.setShortcut('Ctrl+P')
        StopAction.triggered.connect(self.TetrisWidget.stop)
        OptionMenu.addAction(StopAction)
        RestartAction = QAction(QIcon(r'C:\Users\zhong\Desktop\restart.png'), '&Restart', self)
        RestartAction.setStatusTip('Restart the game !')
        RestartAction.setShortcut('Ctrl+R')
        RestartAction.triggered.connect(self.TetrisWidget.restart)
        OptionMenu.addAction(RestartAction)
        SpeedAction = QAction(QIcon(r'C:\Users\zhong\Desktop\speed.png'), '&Speed', self)
        SpeedAction.setStatusTip('Speed the game !')
        SpeedAction.setShortcut('Ctrl+S')
        SpeedAction.triggered.connect(self.TetrisWidget.speed)
        OptionMenu.addAction(SpeedAction)
        self.toolbar = self.addToolBar('Exit')
        exitAction = QAction(QIcon(r'C:\Users\zhong\Desktop\stop.png'), '&Exit', self)
        exitAction.setShortcut('Esc')
        exitAction.triggered.connect(qApp.quit)
        self.toolbar.addAction(exitAction)

        self.resize(600, 500)

        self.center()
        self.setWindowTitle('Tetris')
        self.show()

    def closeEvent(self, event):
        #creating question box when user try to exit the game
        reply = QMessageBox.question(self, 'Message',
                                     'Are you sure to escape?', QMessageBox.Yes | QMessageBox.No, QMessageBox.No)
        if reply == QMessageBox.Yes:
            event.accept()
        else:
            event.ignore()

    def center(self):
        #centers the window on the screen#

        screen = QDesktopWidget().screenGeometry()
        size = self.geometry()
        self.move((screen.width() - size.width()) / 2,
                  (screen.height() - size.height()) / 2)


class TritrisBoard(QFrame):
    next=pyqtSignal(int)
    status = pyqtSignal(str)
    msg2Statusbar = pyqtSignal(str)
    score = pyqtSignal(int)


    TritrisBoardWidth = 16
    TritrisBoardHeight = 22
    Speed = 300
    FastSpeed = 200

    def __init__(self, parent):
        super().__init__(parent)

        self.initTritrisBoard()

    def initTritrisBoard(self):
        #initiates TritrisBoard#
        self.created = False
        self.TritrisBoard = []
        self.clearTritrisBoard()
        self.timer = QBasicTimer()
        self.isWaitingAfterLine = False

        self.curX = 0
        self.curY = 0
        self.numLinesRemoved = 0

        self.setFocusPolicy(Qt.StrongFocus)
        self.isStarted = False
        self.isPaused = False

    def clearTritrisBoard(self):
        #clears shapes from the TritrisBoard#
        self.TritrisBoard = []
        for _ in range((TritrisBoard.TritrisBoardHeight + 2) * TritrisBoard.TritrisBoardWidth):
            self.TritrisBoard.append(Shape.NoShape)

    def start(self):
        #starts game#

        if self.isPaused:
            return
        self.nextPiece = Shape()
        self.nextPiece.setShape(0)
        self.next.emit(self.nextPiece.shape())
        self.isStarted = True
        self.isWaitingAfterLine = False
        self.numLinesRemoved = 0
        self.msg2Statusbar.emit(str(self.numLinesRemoved))
        self.score.emit(self.numLinesRemoved)

        self.newPiece()
        self.timer.start(TritrisBoard.Speed, self)

    def newPiece(self):
        #creates two new shapes#
        if self.nextPiece.shape() == Shape.NoShape:
            self.curPiece = Shape()
            self.curPiece.setRandomShape()


            self.nextPiece = Shape()
            self.nextPiece.setRandomShape()
            self.next.emit(self.nextPiece.shape())
        #create a new shape,and draw last shape
        else:
            self.curPiece=self.nextPiece
            self.nextPiece=Shape()
            self.nextPiece.setRandomShape()
            self.next.emit(self.nextPiece.shape())
        self.curX = TritrisBoard.TritrisBoardWidth // 2 + 1
        self.curY = TritrisBoard.TritrisBoardHeight - 1
        if not self.Move(self.curPiece, self.curX, self.curY):
            self.curPiece.setShape(Shape.NoShape)
            self.timer.stop()
            self.isStarted = False
            self.msg2Statusbar.emit("Game over")
            self.score.emit(0)

    def Move(self, newPiece, newX, newY):
        #tries to move a shape#

        for i in range(4):

            x = newX + newPiece.x(i)
            y = newY + newPiece.y(i)

            if x < 0 or x >= TritrisBoard.TritrisBoardWidth or y < 0:
                return False

            if self.shapeAt(x, y) != Shape.NoShape:
                return False

        self.curPiece = newPiece
        self.curX = newX
        self.curY = newY

        # use update to redraw the board showing the moving piece
        self.update()

        return True

    def timerEvent(self, event):
        #handles timer event#

        if event.timerId() == self.timer.timerId():
            #when removing a full row,set variable isWaitingAfterLine to True,then make a newPiece
            if self.isWaitingAfterLine:
                self.isWaitingAfterLine = False
                self.newPiece()
            else:
                #move curpiece one row down every 300ms(if not changed) in normal times
                self.oneLineDown()

        else:
            super(TritrisBoard, self).timerEvent(event)

    def oneLineDown(self):
        #drop a piece one line done ,if can'not move then it means this piece reached the bottom#
        if not self.Move(self.curPiece, self.curX, self.curY - 1):
            self.pieceDropped()

    def pieceDropped(self):
        #after piece drooped to the bootom, remove lines full of squares and create new shape#

        for i in range(4):
            x = self.curX + self.curPiece.x(i)
            y = self.curY + self.curPiece.y(i)
            self.setShapeAt(x, y, self.curPiece.shape())

        self.removeTetrisWidgetLines()

        if not self.isWaitingAfterLine:
            self.newPiece()

    def removeTetrisWidgetLines(self):
        #removes all TetrisWidget lines from the TritrisBoard#

        numTetrisWidgetLines = 0
        rowsToRemove = []
        #add up rows full of squares into list rowsToRemove
        for i in range(TritrisBoard.TritrisBoardHeight):

            n = sum(
                self.shapeAt(j, i) != Shape.NoShape
                for j in range(TritrisBoard.TritrisBoardWidth)
            )

            if n == self.TritrisBoardWidth:
                rowsToRemove.append(i)
        #process from up to bottom
        rowsToRemove.reverse()

        for m in rowsToRemove:

            for k in range(m, TritrisBoard.TritrisBoardHeight):
                for l in range(TritrisBoard.TritrisBoardWidth):
                    self.setShapeAt(l, k, self.shapeAt(l, k + 1))

        numTetrisWidgetLines += len(rowsToRemove)

        if numTetrisWidgetLines > 0:
            self.numLinesRemoved = self.numLinesRemoved + numTetrisWidgetLines
            self.msg2Statusbar.emit(str(self.numLinesRemoved))
            self.score.emit(self.numLinesRemoved)

            self.isWaitingAfterLine = True
            self.curPiece.setShape(Shape.NoShape)
            self.update()

    def pause(self):
        #pauses game#

        if not self.isStarted:
            return

        self.isPaused = not self.isPaused

        if self.isPaused:
            self.timer.stop()
            self.msg2Statusbar.emit("paused")
            self.status.emit('stopped')

        else:
            self.timer.start(TritrisBoard.Speed, self)
            self.msg2Statusbar.emit(str(self.numLinesRemoved))
            self.score.emit(self.numLinesRemoved)
            self.status.emit('running')

        self.update()

    def paintEvent(self, event):
        #paints all shapes of the game#

        painter = QPainter(self)
        rect = self.contentsRect()

        TritrisBoardTop = rect.bottom() - TritrisBoard.TritrisBoardHeight * self.squareHeight()
        # draw those piece in self.board which  reached the bottom
        for i in range(TritrisBoard.TritrisBoardHeight):
            for j in range(TritrisBoard.TritrisBoardWidth):
                shape = self.shapeAt(j, TritrisBoard.TritrisBoardHeight - i - 1)

                if shape != Shape.NoShape:
                    self.drawSquare(painter,
                                    rect.left() + j * self.squareWidth(),
                                    TritrisBoardTop + i * self.squareHeight(), shape)
        # draw the piece is dropping down which is not in the self.board
        try:
            if self.curPiece.shape() != Shape.NoShape:

                for i in range(4):
                    x = self.curX + self.curPiece.x(i)
                    y = self.curY + self.curPiece.y(i)
                    self.drawSquare(painter, rect.left() + x * self.squareWidth(),
                                    TritrisBoardTop + (TritrisBoard.TritrisBoardHeight - y - 1) * self.squareHeight(),
                                    self.curPiece.shape())
        except:
            return

    def drawSquare(self, painter, x, y, shape):
        #draws a square of a shape#

        colorTable = [0x000000, 0xCC6666, 0x66CC66, 0x6666CC,
                      0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00]

        color = QColor(colorTable[shape])
        painter.fillRect(x + 1, y + 1, self.squareWidth() - 2,
                         self.squareHeight() - 2, color)
        # draw lines surrounding the square
        painter.setPen(color.lighter())
        painter.drawLine(x, y + self.squareHeight() - 1, x, y)
        painter.drawLine(x, y, x + self.squareWidth() - 1, y)

        painter.setPen(color.darker())
        painter.drawLine(x + 1, y + self.squareHeight() - 1,
                         x + self.squareWidth() - 1, y + self.squareHeight() - 1)
        painter.drawLine(x + self.squareWidth() - 1,
                         y + self.squareHeight() - 1, x + self.squareWidth() - 1, y + 1)

    def keyPressEvent(self, event):
        #processes key press events#

        if not self.isStarted or self.curPiece.shape() == Shape.NoShape:
            super(TritrisBoard, self).keyPressEvent(event)
            return

        key = event.key()

        if key == Qt.Key_P:
            self.pause()
            return

        if self.isPaused:
            return

        elif key == Qt.Key_Left:
            self.left()

        elif key == Qt.Key_Right:
            self.right()

        elif key == Qt.Key_Down:
            self.down()

        elif key == Qt.Key_Up:
            self.up()

        elif key == Qt.Key_Space:
            self.dropDown()

        elif key == Qt.Key_D:
            self.oneLineDown()
        elif key == Qt.Key_C:
            self.start()

        else:
            super(TritrisBoard, self).keyPressEvent(event)

    def dropDown(self):
        #quickly drop  a shape to the bottom#

        newY = self.curY

        while newY > 0:

            if not self.Move(self.curPiece, self.curX, newY - 1):
                break

            newY -= 1

        self.pieceDropped()

    def left(self):
        #move the shape to left column
        self.Move(self.curPiece, self.curX - 1, self.curY)

    def right(self):
        #move the shape to  right column
        self.Move(self.curPiece, self.curX + 1, self.curY)

    def up(self):
        #rotate the shape anti-clock
        self.Move(self.curPiece.rotateLeft(), self.curX, self.curY)

    def down(self):
        #rotate the shape clockwise
        self.Move(self.curPiece.rotateRight(), self.curX, self.curY)

    def shapeAt(self, x, y):
        #determines shape at the TritrisBoard position#
        return self.TritrisBoard[(y * TritrisBoard.TritrisBoardWidth) + x]

    def setShapeAt(self, x, y, shape):
        #sets a shape at the TritrisBoard#

        self.TritrisBoard[(y * TritrisBoard.TritrisBoardWidth) + x] = shape

    def squareWidth(self):
        #returns the width of one square#

        return self.contentsRect().width() // TritrisBoard.TritrisBoardWidth

    def squareHeight(self):
        #returns the height of one square#

        return self.contentsRect().height() // TritrisBoard.TritrisBoardHeight
#Board that shows the forthcoming shape
class NextShapeBoard(QFrame):
    BoardWidth = 5
    BoardHeight = 5
    shape=0

    def __init__(self,parent):
        super().__init__(parent)
        self.update()

    def showNext(self,shape):
        if shape == 0:
            return
        self.shape=shape
        self.update()
    def paintEvent(self,event):
        if self.shape == 0:
            return
        painter = QPainter(self)
        rect = self.contentsRect()
        NextBoardTop = rect.bottom() - self.BoardHeight * self.squareHeight()
        for i,j in Shape.coordsTable[self.shape]:
            x = 2 + i
            y = 2 + j
            self.drawSquare(painter, rect.left() + x * self.squareWidth(),
                            NextBoardTop + (self.BoardHeight - y - 1) * self.squareHeight(),
                            self.shape)

    def drawSquare(self, painter, x, y, shape):
        #draws a square of a shape#

        colorTable = [0x000000, 0xCC6666, 0x66CC66, 0x6666CC,
                      0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00]

        color = QColor(colorTable[shape])
        painter.fillRect(x + 1, y + 1, self.squareWidth() - 2,
                         self.squareHeight() - 2, color)
        # draw lines surrounding the square
        painter.setPen(color.lighter())
        painter.drawLine(x, y + self.squareHeight() - 1, x, y)
        painter.drawLine(x, y, x + self.squareWidth() - 1, y)

        painter.setPen(color.darker())
        painter.drawLine(x + 1, y + self.squareHeight() - 1,
                         x + self.squareWidth() - 1, y + self.squareHeight() - 1)
        painter.drawLine(x + self.squareWidth() - 1,
                         y + self.squareHeight() - 1, x + self.squareWidth() - 1, y + 1)

    def squareWidth(self):
        #returns the width of one square#

        return self.contentsRect().width() // self.BoardWidth

    def squareHeight(self):
        #returns the height of one square#

        return self.contentsRect().height() // self.BoardHeight

class Shape(object):
    NoShape = 0
    ZShape = 1
    SShape = 2
    LineShape = 3
    TShape = 4
    SquareShape = 5
    LShape = 6
    MirroredLShape = 7
    coordsTable = (
        ((0, 0), (0, 0), (0, 0), (0, 0)),
        ((0, 0), (0, 1), (-1, 0), (-1, -1)),
        ((0, 0), (-1, 0), (-1, 1), (0, -1)),
        ((0, 0), (0, 1), (0, 2), (0, -1)),
        ((0, 0), (-1, 0), (1, 0), (0, -1)),
        ((0, 0), (0, -1), (1, 0), (1, -1)),
        ((0, 0), (0, 1), (-1, 1), (0, -1)),
        ((0, 0), (0, 1), (1, 1), (0, -1))
    )

    def __init__(self):

        self.coords = [[0, 0] for i in range(4)]
        self.pieceShape = Shape.NoShape

        self.setShape(Shape.NoShape)

    def shape(self):
        #returns shape#

        return self.pieceShape

    def setShape(self, shape):
        #sets a shape#

        table = Shape.coordsTable[shape]

        for i in range(4):
            for j in range(2):
                self.coords[i][j] = table[i][j]

        self.pieceShape = shape

    def setRandomShape(self):
        #create  random shape#

        self.setShape(random.randint(1, 7))



    def x(self, index):
        #returns x coordinate#
        return self.coords[index][0]

    def y(self, index):
        #returns y coordinate#

        return self.coords[index][1]

    def setX(self, index, x):
        #sets x coordinate#

        self.coords[index][0] = x

    def setY(self, index, y):
        #sets y coordinate#

        self.coords[index][1] = y

    def rotateLeft(self):
        #rotates shape to the left#

        if self.pieceShape == Shape.SquareShape:
            return self

        result = Shape()
        result.pieceShape = self.pieceShape

        for i in range(4):
            result.setX(i, -self.y(i))
            result.setY(i, self.x(i))

        return result

    def rotateRight(self):
        #rotates shape to the right#

        if self.pieceShape == Shape.SquareShape:
            return self

        result = Shape()
        result.pieceShape = self.pieceShape

        for i in range(4):
            result.setX(i, self.y(i))
            result.setY(i, -self.x(i))

        return result


class TetrisWidget(QWidget):
    def __init__(self, parent):

        super().__init__(parent)

        self.btns = ['STOP', 'ROTATEL', 'RESTART', 'LEFT', 'ROTATER', 'RIGHT']
        pos = [(i + 1, j + 1) for i in range(2) for j in range(3)]

        self.lcd = QLCDNumber(Qt.Horizontal, self)
        self.btn = QPushButton('START', self)
        self.btn.clicked.connect(self.dealbtn)
        self.btn.setFocusPolicy(Qt.NoFocus)

        self.grid = QGridLayout()
        self.grid.setSpacing(10)

        self.tTritrisBoard = TritrisBoard(self)
        self.nextBoard = NextShapeBoard(self)
        #create buttons above the lcd
        self.grid.addWidget(self.tTritrisBoard, 1, 1, 5, 4)
        for pos, name in zip(pos, self.btns):
            button = QPushButton(name)
            button.setFocusPolicy(Qt.NoFocus)
            if name == 'STOP':
                button.clicked.connect(self.stop)
            elif name == 'ROTATEL':
                button.clicked.connect(self.tTritrisBoard.up)
            elif name == 'RESTART':
                button.clicked.connect(self.restart)
            elif name == 'LEFT':
                button.clicked.connect(self.tTritrisBoard.left)
            elif name == 'ROTATER':
                button.clicked.connect(self.tTritrisBoard.down)
            elif name == 'RIGHT':
                button.clicked.connect(self.tTritrisBoard.right)
            else:
                return
            self.grid.addWidget(button, pos[0], pos[1] + 4)
        self.grid.addWidget(self.nextBoard,3,5,1,3)
        self.grid.addWidget(self.lcd, 4, 5, 1, 3)
        self.grid.addWidget(self.btn, 5, 5, 1, 3)
        #show the score in lcd
        self.tTritrisBoard.score[int].connect(self.lcd.display)
        #handle tetris_board's operating status
        self.tTritrisBoard.status[str].connect(self.handle_status)
        #handle next shape signal
        self.tTritrisBoard.next[int].connect(self.nextBoard.showNext)
        self.tTritrisBoard.status.emit('wait_start')

        self.setLayout(self.grid)

    def start(self):
        if self.btn.text() == 'START' and not self.tTritrisBoard.timer.isActive():
            self.tTritrisBoard.start()
            self.tTritrisBoard.status.emit('running')

    def stop(self):
        self.tTritrisBoard.pause()

    def speed(self):
        self.tTritrisBoard.timer.stop()
        self.tTritrisBoard.timer.start(TritrisBoard.FastSpeed, self.tTritrisBoard)

    def restart(self):
        if not self.tTritrisBoard.timer.isActive():
            self.tTritrisBoard.pause()
        self.tTritrisBoard.clearTritrisBoard()
        self.tTritrisBoard.start()
        self.tTritrisBoard.status.emit('running')

        self.tTritrisBoard.msg2Statusbar.emit('Successly restarted,Good luck!')
    #change the start_button's text follwing the signal of tetris_board's operating status
    def handle_status(self, status):
        if status == 'wait_start':
            self.btn.setText('START')

        elif status == 'running':
            self.btn.setText('STOP')

        elif status == 'stopped':
            self.btn.setText('CONTINUE')

        else:
            return
    #control the function of start_button
    def dealbtn(self):
        if self.btn.text() == 'START':
            self.start()
        elif self.btn.text() == 'STOP':
            self.stop()
        elif self.btn.text() == 'CONTINUE':
            self.stop()
        else:
            return


if __name__ == '__main__':
    app = QApplication([])
    tetris = Main()
    sys.exit(app.exec_())
