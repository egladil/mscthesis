compile = runghc Compile 

all: demo missing

demo: compdemo linkdemo

compdemo:
	$(compile) -opt Eng Ger Swe DisambMountaineeringEng

linkdemo:
	$(compile) -link Eng Ger Swe DisambMountaineeringEng

missing:
	echo "pg -missing | wf -file=missing.txt" | gf -run Mountaineering.pgf 
