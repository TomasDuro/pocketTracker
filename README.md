# SelfieDrone

This repository contains the code used and developed during the master thesis entitled: "Tracking and Following a Moving Person Onboard a Pocket Drone”.

Used operative system: Ubuntu 14.04.5 LTS

## Trackers

Code for the three trackers used in this work. The code for KCF and Struck suffered a few alterations, but the core remains the same as in http://www.robots.ox.ac.uk/~joao/circulant/ and http://www.samhare.net/research/struck, respectively. The third tracker is the Pocket Tracker which was developed during this work. The code for the pocket tracker can be directly implemented on the stereo vision board.

## Matlab

The prototype code of the Pocket Track as well as the code used to build data sets and train the parameters of the detector, respectively PocketTracker.m, PocketAnnotate.m and PocketTrainer.m.