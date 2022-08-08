# AJ2 Tool

# Normalize Tool

## Pre condition

Make environment on Ubuntu 20.4 or Later version

---
sudo apt update

sudo apt upgrade

sudo apt install build-essential cmake git

sudo apt install pkg-config

sudo apt install libopencv-dev


---

## Build Tool

---

git clone https://github.com/swchoi85/AJ2Tool.git

cd AJ2Tool/Normalize/source

make

---


## Processing Step

Put Image in the "Iris" folder and then command

| Command                        | Description                                           |
|--------------------------------|-------------------------------------------------------|
| `./trans`                      | Make image modified files from 'Iris' -> 'Trans'      |
| `./normal`                     | Make image modified files from 'Trans' -> 'Conv'      |


### trans output

Original Image

<img src="https://user-images.githubusercontent.com/75821638/183318401-f5c2ed1d-6bbd-4da1-808c-e4018d41b0bc.png" width="320" height="240">

Rotate Image

<img src="https://user-images.githubusercontent.com/75821638/183318611-c0ddb1dc-2d4e-46c9-9ac4-4ad1926d06c1.png" width="320" height="240">

3D Rotate Image

<img src="https://user-images.githubusercontent.com/75821638/183318630-2b0fe87e-2669-4972-a948-ce0f4b97bf83.png" width="320" height="240">

Gamma effect

<img src="https://user-images.githubusercontent.com/75821638/183318888-747d0869-e2f2-46f9-a297-e7129406d9df.png" width="320" height="240">


### Normalize Outout

Checked Iris Image

<img src="https://user-images.githubusercontent.com/75821638/183318961-dc93b945-5d61-4d8b-91c3-0a8ddc6ba3f1.png" width="320" height="240">

Normalized Image

<img src="https://user-images.githubusercontent.com/75821638/183318998-06180867-986e-4307-aa3a-076b8440dd5d.png" width="600" height="150">

