### Features
- support `systemctl` and `systemd` command. This feature comes directly from `centos/systemd`.
    - Must run in `--priviledged` mode.
- support `sshd` service. The default root password is `root`.
- support nfs sharing among containers. This is done by setting up a volumn.
    - The exported path must be within the volume named `exports`.

### Usage

```
docker run -d -p 2222:22 --name node1 --privileged zhqu1148980644/centos7-systemd-sshd usr/sbin/init
ssh -p 2222 localhost
```

### Dockerfile
```dockerfile
FROM centos/systemd
LABEL maintainer="zhqu1148980644 zhongquan789@gmail.com"

RUN ( yum update -y; \
      # Update System and install essential packs
      yum install -y openssh-server initscripts epel-release wget passwd tar unzip ;\
      # Configure OpenSSH-Server (Part. 1)
      sed -i 's/UsePAM yes/#UsePAM yes/g' /etc/ssh/sshd_config; \
      sed -i 's/#UsePAM no/UsePAM no/g' /etc/ssh/sshd_config; \
      sed -i 's/#PermitRootLogin yes/PermitRootLogin yes/' /etc/ssh/sshd_config; \
      # Configure OpenSSH-Server (Part. 2)
      mkdir -p /root/.ssh/; \
      echo "StrictHostKeyChecking=no" > /root/.ssh/config; \
      echo "UserKnownHostsFile=/dev/null" >> /root/.ssh/config; \
      # Configure SSH Key
      ssh-keygen -A ;\
      # Configure yum repo
      sed -i 's/enabled=0/enabled=1/' /etc/yum.repos.d/CentOS-Base.repo; \
      # Set the root password
      echo "root:root" | chpasswd ;\
      # Cleaning up images
      yum clean all ;\
      rm -rf /var/cache/yum )

RUN mkdir -p /exports
# incase need file sharing among containers using nfs...
VOLUME /exports

EXPOSE 22
CMD /usr/sbin/sshd -D
```
