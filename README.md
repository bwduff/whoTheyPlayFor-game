# Who they play for?? - Quiz yourself and the computer with basketball trivia!

If you're a basketball fanatic, you may be familiar with the popular NBA show on TNT, "Inside the NBA". After each off-season, the Inside crew play a game called "Who he play for?", in which contestants must guess which team a given player now plays for. This can be challenging (even for hardcore fans) given that many free agent signings and trades happen within the off-season. You can check out one example of the segment on [YouTube](https://youtu.be/xuJGzw8rzSs).

In this program (which I've written for my own education and reference), quiz yourself and/or the computer as to which team a given player plays for.
This program will initially be focused on players and teams from the NBA, but could in the future be extended to include the WNBA, college, and international teams.

## Project Goals:

As a self-educational programming project, the main goal is to **MAKE LEARNING FUN!**
In terms of specifics, I aim to incorporate various features that require different technical skillsets. These features will be introduced in different phases and include things such as: CSV file input (for updating rosters quickly), DNN-based face recognition (to quiz the computer without providing a name), basic computer graphics to provide a more interactive game including player pictures and scores, and more.

This project will be specifically developed for the NVIDIA Jetson Nano 2GB developer's kit, but of course it should be generalizable to any (Linux) machine with the appropriate packages. 

### Build / execution instructions

TODO: Update

## Project Roadmap:

#### **(PLAN: December 2021)** 

**Basic I/O** - Running as a linux console program, the program will first support text queries and results. Unlike like the Inside the NBA game, instead of a user being presented with a player's name and photo, initially this program will be a query-based look-up program. That is, users can type in the name of a given player and learn who they play for. I will develop this first to facilitate testing and further development.

**Face Recognition** - As a computer vision enthusiast, I would like to quiz a DNN model which team a player plays for without even giving the program a name. Instead, I would like to provide an unannotated (but cropped) photo to a classifier CNN (such as MobileNet) and see if the program can correctly guess which player it is, and therefore enable the program to refer to its internal database of teams and players and tell me who the player plays for. I will identify and detail the training process for this model within this repo.

**Advanced roster control** - Initially, I plan to build this program with a small subset of players and teams, and later expand to cover the whole of active players in the NBA. To easily facilitate this, I will add a CSV backend to allow easy offline updates of rosters. I plan to retrieve data from reference websites such as [Basketball-reference.com](https://www.basketball-reference.com/teams/GSW/2021.html#all_roster).

#### **(PLAN: January-Feb 2022)**
**Game mode** - Naturally, the spirit of this project is that of a game. As such, an important portion of development will entail incorporating rudimentary computer graphics, controls, and display to have the user (or opposing contestants) try to guess answers when quizzed. As a standalone game, this would usually take priority ahead of CV related features. However, again, as I am using this project for my own education, this will be a lower priority.

#### **(PLAN: Late 2022-?)**
Audio input - What's a game without buzzers and shouting contestants? Eventually, I would like to learn more about speech recognition and processing, and take this project to the living room or half-time happy hour. This is admittedly a stretch goal as I have no prior exposure to speech recognition, but nonetheless it provides a fun environment in which to learn it.
