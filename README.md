# Particle-Equilibrium-Simulation

This simulation was used to solve a mechanical experiment of approximating the point of equilbrium between 3 different springs attached to each other on a plane using Newton–Raphson method. 

The Experiment / Background:
- We want to pin 3 different springs to a plane, attach their ends together, and know exactly where the equilibium point will end up on the plane. Newton’s first law tells us that the when the sum of the net total forces on an object are balanced, then the system’s mass times acceleration of that system is zero. Therefore, we can apply this law to a set of three spring which are attached to each other, and there loose ends are pinned to a particle board. The three springs will reach an equilibrium, and the center of those three springs will migrate to a certain position on that particle board. That migration of the springs’ center, denoted (xc, yc), will depend on the following equilibrium formula:

					                 ∑Fi = 0						(1)	

- Here, Fi is the magnitude of the individual spring force, given by the following formula:
		
				                      Fi = Fi˳ + ki (Li – Li˳)    				(2)

- In the above equation, Fi˳ is the non-zero tensile force of each spring, ki is the linear spring constant, Li is the length of the spring with a tensile force applied, and Li˳ is the free length of the spring. For us to verify equation 1, the spring’s free and stretched lengths, the spring angles θi, and the spring constants must be measured. The spring constant ki are measured using known weights and then measuring the stretch of the spring length.


The Simulation: 
- The simulation takes in the following data for each spring via a prompt or text file: 
  - Spring Constant (Newton/Meters)
  - Compressive Force Constant (Newtons)
  - Free Length of Springs (Meters)
  - Spring location (Cartesian Coordinates - Inches)
  - Equilibrium point guess (Cartesian Coordinates - Inches)
  
- The simulation returns
  - Final equilibrium position (Cartesian Coordinates - Inches)
  - Final equilibrium angles (degrees)
  - Final lengths of springs under tension (Meters)
  - Actual force on each spring once in equilibirum (Newtons)
