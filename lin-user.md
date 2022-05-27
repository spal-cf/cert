
useradd test - Add user test

useradd -m test - Add user test and create home folder

useradd -d/home/test -m test - add user and create specified home folder

useradd -gacct test
useradd -gacct -Git test - add user to groups acct and it

usermod -Gmanagement test - add existing test user to management group

usermod -d/home/test1 test

uerdel test

useradd -p $(openssl passwd -crypt $PASS) $USER
