# AlkaidTool

## Pre Condition

Install required tools

### Raspiberrypi 4

Due to conflic between Opencv and Qt you shold install *opencv-python-headless* 

```

sudo apt install python3-pyqt5

sudo apt install libopencv-dev

pip3 install opencv-python-headless


git clone https://github.com/swchoi85/AJ2Tool.git

cd AJ2Tool/alkaidApp

cp Lib/aj2lib.so.arm64_py3.9 aj2lib.so

```

### Jecson Nano

```

sudo apt install python3-pyqt5

sudo apt install libopencv-dev

pip3 install opencv-python-headless

git clone https://github.com/swchoi85/AJ2Tool.git

cd AJ2Tool/alkaidApp

cp Lib/aj2lib.so.arm64_py3.6 aj2lib.so


```


Run PKG

```

python3 main.py


```
