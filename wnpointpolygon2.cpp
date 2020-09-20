
#include <stdio.h>     // - Just for some ASCII messages
#include <GL/glut.h>   // - An interface and windows management library

////////////////// State Variables ////////////////////////
struct Point2D	
{
   float x;
   float y;
}p,V[5],P1,P2,P3;

float angle = 0.0f;

void DrawAxes()
{
    glColor3f(1.6, 1.6, 1.6);
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.0);
    glVertex2f(100.0, 0.0);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.0, 100.0);
    
    glEnd();
}
void Idle()
{
    angle += 1.0f;
    glutPostRedisplay();
}
void Resize(int w, int h)
{
    // define the visible area of the window ( in pixels )
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);

    // Setup viewing volume

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //         L	   R 	  B 	T	 N	   F
    glOrtho(-100.0, 100.0, -100.0, 100.0, 100.0, -100.0);

}

void Render()
{

    glClear(GL_COLOR_BUFFER_BIT); // Clean up the colour of the window
    // and the depth buffer

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    DrawAxes();
  	//glRectf(V[0].x,V[0].y, V[3].x, V[3].y); // Draw polygon
  	
  	int p1[]={V[0].x,V[0].y};
	int p2[]={V[1].x,V[1].y};
	int p3[]={V[2].x,V[2].y};
	int p4[]={V[3].x,V[3].y};
	int p5[]={V[4].x,V[4].y};
	int p6[]={V[5].x,V[5].y};
	glBegin (GL_POLYGON);
	glColor3f(0.0,0.5,10.0);
	
	glVertex2iv (p1);
	glVertex2iv (p2);
	glVertex2iv (p3);
	glVertex2iv (p4);
	glVertex2iv (p5);
	glVertex2iv (p6);
	glFlush();
	glEnd();
  	glBegin(GL_POINTS);
    glColor3f(0.2, 0.9, 0.2);
    glPointSize(150);
    
      
    
    glVertex2f(p.x, p.y);	//point
      
    
    glEnd();
	 
	glutSwapBuffers();
}

int isLeft( Point2D P0, Point2D P1, Point2D P2 )	//computing if a point P1 is left of P2 or not
{
    return ( (P1.x - P0.x) * (P2.y - P0.y)
            - (P2.x -  P0.x) * (P1.y - P0.y) );
}

int wn_PnPoly( Point2D p, Point2D V[], int n )
{
    int    wn = 0;    // the  winding number counter
    
	/*V[0].x=10.0; V[0].y=10.0;
    V[1].x=35.0; V[1].y=10.0; 
    V[2].x=35.0; V[2].y=45.0;
    V[3].x=10.0; V[3].y=45.0;*/

    // loop through all edges of the polygon
    for (int i=0; i<n; i++) {   // edge from V[i] to  V[i+1]
        if (V[i].y <= p.y) {          // start y <= P.y
            if (V[i+1].y  > p.y)      // an upward crossing
                 if (isLeft( V[i], V[i+1], p) > 0)  // P left of  edge
                     ++wn;            // have  a valid up intersect
        }
        else {                        // start y > P.y (no test needed)
            if (V[i+1].y  <= p.y)     // a downward crossing
                 if (isLeft( V[i], V[i+1], p) < 0)  // P right of  edge
                     --wn;            // have  a valid down intersect
        }
    }
    return wn;
}
int cn_PnPoly( Point2D p, Point2D V[], int n)	//n oi pleyres
{
    int    cn = 0;    // the  crossing number counter
	int i;
	
	/*V[0].x=10.0; V[0].y=10.0;
    V[1].x=35.0; V[1].y=10.0; 
    V[2].x=35.0; V[2].y=45.0;
    V[3].x=10.0; V[3].y=45.0;*/
    
    // loop through all edges of the polygon
    for (int i=0; i<n; i++) {    // edge from V[i]  to V[i+1]
       if (((V[i].y <= p.y) && (V[i+1].y > p.y))     // an upward crossing
        || ((V[i].y > p.y) && (V[i+1].y <=  p.y))) { // a downward crossing
            // compute  the actual edge-ray intersect x-coordinate
            float vt = (float)(p.y  - V[i].y) / (V[i+1].y - V[i].y);
            if (p.x <  V[i].x + vt * (V[i+1].x - V[i].x)) // P.x < intersect
                 ++cn;   // a valid crossing of y=P.y right of P.x
        }
    }
    return (cn&1);    // 0 if even (out), and 1 if  odd (in)

}

void Setup() // DON'T TOUCH IT
{
    //Parameter handling
    //glShadeModel (GL_SMOOTH);
    glShadeModel(GL_FLAT);

    // polygon rendering mode
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    //Set up light source
    GLfloat light_position[] = {-50.0, 20.0, 150.0, 1.0};
    GLfloat ambientLight[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat diffuseLight[] = {0.8, 0.8, 0.8, 1.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_POINT_SMOOTH);

    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    

}

int main(int argc, char* argv[])
{
    // initialize GLUT library state    
    glutInit(&argc, argv);
    int chose;
    printf("Choose method (for cn1 and wn2)\n");
    scanf("%d",&chose);
    int i;
		for(i=0;i<6;i++){
			printf("\n%d point\n",i);
			scanf("%f",&V[i].x);
			scanf("%f",&V[i].y);	
		}
		for(i=0;i<6;i++){
			printf("\n%f %f for V\n",V[i].x,V[i].y);
				
		}
		
    if(chose==1){
    	printf("please give the point you want(x,y)\n");
	    scanf("%f",&p.x);
		scanf("%f",&p.y);
		int value;
		value=wn_PnPoly( p, V, 6);
		if(value==0){
			printf("The point is outside the polygon");
		}
		else{
			printf("The point is inside the polygon");
		}
	
	}
	else{
		printf("please give the point you want(x,y)\n");
	    scanf("%f",&p.x);
		scanf("%f",&p.y);
		printf("please give the verticle you want(x,y)\n");
		
		int value;
		value=cn_PnPoly( p, V, 6);
		if(value==0){
			printf("The point is outside the polygon");
		}
		else{
			printf("The point is inside the polygon");
		}
	}
    
    // Set up the display using the GLUT functions to
    // get rid of the window setup details:
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);


    // Define the main window size and initial position
    // ( upper left corner, boundaries included )
    glutInitWindowSize(480, 480);
    glutInitWindowPosition(50, 50);

    // Create and label the main window
    glutCreateWindow("Point in Polygon");

    // Configure various properties of the OpenGL rendering context
    Setup();

    // Callbacks for the GL and GLUT events:

    // The rendering function
    glutDisplayFunc(Render);
    glutReshapeFunc(Resize);

    //Enter main event handling loop
    glutMainLoop();
    return 0;


}
