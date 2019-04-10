[![Build Status](https://travis-ci.com/nevrome/gluesless.svg?token=vxsQ9RjxoGASGtX4Q8jc&branch=master)](https://travis-ci.com/nevrome/gluesless)

## gluesless

gluesless is an idea expansion simulation. 

A miminal working example application can be explored [here](https://github.com/nevrome/popgen.styletrans.saa2019/tree/master/code). More documentation will be added in the future. 

```
gluesless -pi <path_to_file> -ii <path_to_file> -o <path_to_file>

 Options:
  -pi --pajekfile	text file that describes network in .pajek format
  -ii --ideasfile	text file that describes idea as produced by popgenerator
  -o --outputfile	output text file
  -q --quiet
```

## Installation

```
sudo apt-get install -y libboost-all-dev libiomp-dev zip unzip
wget "http://snap.stanford.edu/releases/Snap-4.0.zip"  
unzip Snap-4.0.zip -d snap_raw
mkdir snap
cp -r snap_raw/Snap-4.0/* snap
cd snap
make
cd ..
git clone git@github.com:nevrome/gluesless.git
cd gluesless
make
```

## Citation

```
@Manual{clemens_schmid_gluesless_2018,
  address = {Kiel},
  title = {Gluesless: {{An}} Idea Expansion Simulation},
  author = {{Clemens Schmid}},
  year = {2018}
}
```
