compile = runghc Compile 

all: demo missing

demo: compdemo linkdemo

compdemo:
	$(compile) -opt Eng Ger Swe

linkdemo:
	$(compile) -link Eng Ger Swe

missing:
	echo "pg -missing | wf -file=missing.txt" | gf -run Mountaineering.pgf 
