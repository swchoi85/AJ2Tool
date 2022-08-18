# AlkaidTool

Sample App to use Mizar

<img src="https://user-images.githubusercontent.com/75821638/185293668-754b29a6-8dca-49df-a3b4-e5ad05025f82.jpg" width="320" height="240">


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

pip3 install PyQt5

pip3 install opencv-python-headless

git clone https://github.com/swchoi85/AJ2Tool.git

cd AJ2Tool/alkaidApp

cp Lib/aj2lib.so.arm64_py3.6 aj2lib.so


```


Run PKG

```

python3 main.py

```

To capture Iris image, Click Start and then click capture

To identify Iris and pupil press Identify button

*Will be added Enroll and real Identify features.*

<img src="https://user-images.githubusercontent.com/75821638/185295669-4edfbeda-dfb6-450f-834e-d94432d20762.jpg" width="600" height="350">
