# 18-19-7405N
repo for 2018-2019 MHS 7405N VEX

code is located in three file: aton.cpp, init.cpp, opcontrol.cpp, in dir src

i honestly dont know why im writing this readme, but we're prob gonna have to be up l8 for this and we're gonna have to refer to
this bc we're just exhausted beyond fucking belief

so if there are any notes or whatever just who cares anymore 

for pros, there are a few main functions:
-prosv5 - gets you the info
 		make - compile
 		upload - upload to v5 brain
 		mu - short for make and upload(does both)
 		condcutor new-project [dir] - makes a new pros project in the specified directory

we're gonna use this mostly bc im not about to use some trash ass ide (vcs) thatll take 1304912309 years to start up, 
so im just gonna stick with sublime

basic git commands: 
git - help, shows commands
	add . - adds changes to what you want to commit (im not totally sure what this does but you need to do it)
	commit -m"message" - commits changes w/ a commit message (replace message in quotes) - pls try to make these helpful so we know whats going on with the code
	push - pushes the commit to master branch

^^you have to use these commands in order to publish changes to the repo, DO NOT COMMIT W/O TELLING SOMEONE ELSE
for ex. if yo uand someone else make changes to the same file, and you both try to commit, the universe will fuckign explode and we'll have to deal with annoying merge errors so pls spare me

other important git commands: 
	clone "https://github.com/profilename/reponame" - clones the repo to ur computer, for ex. for this repo, you clone it by :
		git clone "https://github.com/mehulghosal/18-19-7405N"
	stash - this restores changes to the last commit, good of rstuff that doesnt work, or for avoiding merge errors