// Program takes in characterstics of 3 springs and calculates and equilibrium center position

#define _CRT_SECURE_NO_DEPRECATE 1
#define _CRT_NONSTDC_NO_DEPRECATE 1

#include <stdio.h>
#include <conio.h>
#include <math.h>

// Function Protocols
void Initialize();
void Calibrate();
void develop_eqn();
void newton_meth();
void showtime();

//-------------------------------------------------DECLARATIONS-------------------------------------//

#define axe 39.37007874       // Conversion variable 1 Inch = 0.0254m

   double kg = 30,	         // Spring constants Newton/Meters
          kb = 27.5,
          kr = 25;  

	double f0g = 0.8,	         // Initial force constant    Newtons
          f0b = 0.6,
          f0r = 1.0; 

   double L0g = 0.160,           // Free lengths of springs
          L0b = 0.155, 
          L0r = 0.150;   

   double configxg = 2 / axe,    // Spring Coordinates Inches -> Meters
          configyg = 2 / axe,
          configxb = 23 / axe,
          configyb = 21/ axe,
          configxr = 14/ axe,
          configyr = 23 / axe; 

   double xc ;                   // Center ring x position
   double yc ;                   // Center ring y position
   double thetag, thetab, thetar;
   double lambdag, lambdab, lambdar;
   double fg, fr, fb;		      // Actual force on spring
   double Lg, Lb, Lr;            // Lengths of spring under tension
   double a;                     // phi x
   double b;                     // die phi y / die yc
   double c;                     // phi y
   double d;                     // die phi x / die yc.....die phi y / die xc
   double e;                     // die phi x / die xc

   int iter = 1,
       itermax = 60;		

   double alpha = 0.5;           // Undderrelaxation factor
   double maxerrx = 0.0000000000343566195;
   double maxerry = 0.0000000000244189619; 
  

   double Xcn0 = 14 / axe,      // Initial guess of center position Inches -> Meters
          Ycn0 = 14 / axe,
          Xcn1,             
          Ycn1;

   double deltal;   // Reserved for error




//-------------------------------------------------MAIN FUNCTION-------------------------------------// 


int main()
{
  Initialize();           // Prompt for Values
   
   printf("\nInitial Guess X: %.2f Y: %.2f\n\n", Xcn0*axe ,Ycn0*axe);

   while(iter != itermax)
   {

   develop_eqn();            // Udate new values for Newtons Method
   newton_meth();            // Newtons Method with Underrelaxation

   printf("X: %lf\tY: %lf\tIteration # %d\n", xc * axe, yc * axe, iter);

   if(deltal < 10e-6)
      {
         iter = itermax;     // Exit Loop
      }
      else
      {
         Xcn0 = xc;          // Set current iteration's values as old
         Ycn0 = yc;
         iter++;
      } 

   } // End While

   showtime();               // Print Results

   printf("\nPress any key to exit");
   getch();
}




//-------------------------------------------------------FUNCTIONS---------------------------------------------------------------//



//--------------------------------------------UPDATE NEW VALUES FOR NEWTON--------------------------------//
void develop_eqn()
   {

   Calibrate();    // Recal Length, Force, Lamda 
   
   a = (fg * ((configxg - Xcn0) / Lg) + (fb * ((configxb - Xcn0) / Lb) + (fr * ((configxr - Xcn0) / Lr)))); //di x
   c = (fg * ((configyg - Ycn0) / Lg) + (fb * ((configyb - Ycn0) / Lb) + (fr * ((configyr - Ycn0) / Lr)))); //di y
   //di phi x / di xc
   e = ((lambdag * (pow((configxg - Xcn0) / Lg, 2) - fg) / Lg) + (lambdab * (pow((configxb - Xcn0) / Lb, 2) - fb) / Lb) + (lambdar * (pow((configxr - Xcn0) / Lr, 2) - fr) / Lr)); 
   //di phi y / di yc
   b = ((lambdag * (pow((configyg - Ycn0) / Lg, 2) - fg) / Lg) + (lambdab * (pow((configyb - Ycn0) / Lb, 2) - fb) / Lb) + (lambdar * (pow((configyr - Ycn0) / Lr, 2) - fr) / Lr));
   //di phi x / di yc
   d = ((lambdag / Lg) * ((configxg - Xcn0) / Lg) * ((configyg - Ycn0) / Lg)) + 
       ((lambdab / Lb) * ((configxb - Xcn0) / Lb) * ((configyb - Ycn0) / Lb)) + 
       ((lambdar / Lr) * ((configxr - Xcn0) / Lr) * ((configyr - Ycn0) / Lr));  

   Xcn1 = (((a * b) - (c * d)) /
             ((e * b) - (d * d)));		 

   Ycn1 = (((-a * d) + (c * e)) /
             ((e * b) - (d * d)));

   deltal = sqrt((Xcn1*Xcn1) + (Ycn1*Ycn1));   // Recal Error 
   }


//--------------------------------------------SOLVE FORCE LENGTH LAMDA FUNCTION---------------------------------//
void Calibrate()
   {
   // Lenth of spring = Xguess center - Spring coordinate
   Lg = sqrt(pow((configxg - Xcn0), 2) + pow((configyg - Ycn0), 2));
   Lb = sqrt(pow((configxb - Xcn0), 2) + pow((configyb - Ycn0), 2));
   Lr = sqrt(pow((configxr - Xcn0), 2) + pow((configyr - Ycn0), 2));
   // Force on spring
   fg = f0g + (kg * (Lg - L0g));
   fb = f0b + (kb * (Lb - L0b));
   fr = f0r + (kr * (Lr - L0r));
   // Lamda costant
   lambdag = f0g - (kg * L0g);     
   lambdab = f0b - (kb * L0b);
   lambdar = f0r - (kr * L0r);
   }


//------------------------------------NEWTONS METHOD FUNCTION WITH UNDERRELAXATIONS---------------------------------//
void newton_meth()
   {
   // Newtons Method 
   xc = (Xcn1) + (Xcn0);
   yc = (Ycn1) + (Ycn0);
   // Underrelaxation                                
  // xc = ((1-alpha) * Xcn0) + (alpha * xc);
  // yc = ((1-alpha) * Ycn0) + (alpha * yc);
   }



//-------------------------------------------PRINT RESULTS FUNCTION---------------------------------//
void showtime()
   {
   // Lenth of spring = Xguess center - Spring coordinate
   Lg = sqrt(pow((configxg - xc), 2) + pow((configyg - yc), 2));
   Lb = sqrt(pow((configxb - xc), 2) + pow((configyb - yc), 2));
   Lr = sqrt(pow((configxr - xc), 2) + pow((configyr - yc), 2));
   // Force on spring
   fg = f0g + (kg * (Lg - L0g));
   fb = f0b + (kb * (Lb - L0b));
   fr = f0r + (kr * (Lr - L0r));
   // Angles from X
   thetag = atan2(((configyg - yc) / Lg),((configxg - xc) / Lg));      // Theta for each spring from postive x axis
   thetab = atan2(((configyb - yc) / Lg),((configxb - xc) / Lg));  
   thetar = atan2(((configyr - yc) / Lg),((configxr - xc) / Lg));  
   thetag *= (180/3.1416);      // Theta for each spring from postive x axis
   thetab *= (180/3.1416);
   thetar *= (180/3.1416);
   
   if (thetag < 0)
      {
         thetag += 360;
      }

   if (thetab < 0)
      {
         thetab += 360;
      }

   if (thetar < 0)
      {
         thetar += 360;
      }

   // Print Results
   printf("\nREACHED EQUILIBRUM AT X = %lf Y: %lf \n", xc * axe, yc * axe);
   printf("\nSPRING FORCE:     Green: %lf N    Blue: %lf N    Red: %lf N\n", fg, fb, fr);
   printf("LENGTH OF SPRING: Green: %lf m    Blue: %lf m    Red: %lf m\n", Lg, Lb, Lr);
   printf("\ANGLE FROM X:     Green: %.2lf deg   Blue: %.2lf deg    Red: %.2lf deg\n", thetag, thetab, thetar);
   }

//--------------------------------------------------PROMPT FUNCTION-------------------------------------//
void Initialize()
   {
   /*
   // SPRING CONSTANTS
   printf("\nPlease enter the SPRING CONSTANT in 'N/m' for \nGREEN spring: ");
   scanf("%lf", &kg);

   printf("BLUE spring: ");
   scanf("%lf", &kb);

   printf("RED spring: ");
   scanf("%lf", &kr); 

   // COMPRESSIVE FORCE CONSTANTS
   printf("\n\nPlease enter the COMPRESSIVE FORCE CONSTANT in 'N' for \nGREEN spring: ");
   scanf("%lf", &f0g);

   printf("BLUE spring: ");
   scanf("%lf", &f0b);

   printf("RED spring: ");
   scanf("%lf", &f0r);

   // FREE LENGTHS
   printf("\n\nPlease enter the FREE LENGTHS in 'm' for the \nGREEN spring: ");
   scanf("%lf", &L0g);

   printf("BLUE spring: ");
   scanf("%lf", &L0b);

   printf("RED spring: ");
   scanf("%lf", &L0r);
  */

   // CONFIGURATIONS COORDIANTES
   printf("\nPlease enter the coordinates for the \nGREEN spring\n");
   printf("X: ");
   scanf("%lf", &configxg);
   printf("Y: ");
   scanf("%lf", &configyg);

   printf("\nBLUE spring\n");
   printf("X: ");
   scanf("%lf", &configxb);
   printf("Y: ");
   scanf("%lf", &configyb);

   printf("\nRED spring\n");
   printf("X: ");
   scanf("%lf", &configxr);
   printf("Y: ");
   scanf("%lf", &configyr);

         // CONVERT INCHES TO m
          configxg /= axe;
          configyg /= axe;
          configxb /= axe;
          configyb /= axe; 
          configxr /= axe; 
          configyr /= axe; 

    // RING CENTER GUESS
   printf("\n\nPlease your CENTER RING COORDINATE guess\nX: ");
   scanf("%lf", &Xcn0);
   printf("Y: ");
   scanf("%lf", &Ycn0);

         // CONVERTS INCHES TO m
         Xcn0 /= axe; 
         Ycn0 /= axe; 


   }