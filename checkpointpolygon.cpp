#include <stdio.h>     // - Just for some ASCII messages
#include <GL/glut.h>   // - An interface and windows management library
#include<stdlib.h> //includes the standard library header file

float r,g,b;
bool check=true;
int chose,pleyres,click_count=0;
struct Point2D	
{
   float x;
   float y;
}p,V[10];

float angle = 0.0f;

void Draw()
{
    int p1[]={V[0].x,V[0].y};
	int p2[]={V[1].x,V[1].y};
	int p3[]={V[2].x,V[2].y};
	int p4[]={V[3].x,V[3].y};
	int p5[]={V[4].x,V[4].y};
	int p6[]={V[5].x,V[5].y};
	int p7[]={V[6].x,V[6].y};
	int p8[]={V[7].x,V[7].y};
	int p9[]={V[8].x,V[8].y};
	int p10[]={V[9].x,V[9].y};
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.4,0.1);
	//glColor3f(0.0, 0.0, 0.0);
	glBegin (GL_POLYGON);
	if(pleyres==3){
		glVertex2iv (p1);
		glVertex2iv (p2);
		glVertex2iv (p3);
		glVertex2iv (p1);
	}
	else if(pleyres==4){
		glVertex2iv (p1);
		glVertex2iv (p2);
		glVertex2iv (p3);
		glVertex2iv (p4);
		glVertex2iv (p1);
	}
	else if(pleyres==5){
		glVertex2iv (p1);
		glVertex2iv (p2);
		glVertex2iv (p3);
		glVertex2iv (p4);
		glVertex2iv (p5);
		glVertex2iv (p1);	
	}
	else if(pleyres==6){
		glVertex2iv (p1);
		glVertex2iv (p2);
		glVertex2iv (p3);
		glVertex2iv (p4);
		glVertex2iv (p5);
		glVertex2iv (p6);
		glVertex2iv (p1);
	}
	else if(pleyres==7){
		glVertex2iv (p1);
		glVertex2iv (p2);
		glVertex2iv (p3);
		glVertex2iv (p4);
		glVertex2iv (p5);
		glVertex2iv (p1);
		glVertex2iv (p6);
		glVertex2iv (p7);
		glVertex2iv (p1);
	}
	else if(pleyres==8){
		glVertex2iv (p1);
		glVertex2iv (p2);
		glVertex2iv (p3);
		glVertex2iv (p4);
		glVertex2iv (p5);
		glVertex2iv (p1);
		glVertex2iv (p6);
		glVertex2iv (p7);
		glVertex2iv (p8);
		glVertex2iv (p1);
	}
	else if(pleyres==9){
		glVertex2iv (p1);
		glVertex2iv (p2);
		glVertex2iv (p3);
		glVertex2iv (p4);
		glVertex2iv (p5);
		glVertex2iv (p1);
		glVertex2iv (p6);
		glVertex2iv (p7);
		glVertex2iv (p8);
		glVertex2iv (p9);
		glVertex2iv (p1);
	}
	else{
		glVertex2iv (p1);
		glVertex2iv (p2);
		glVertex2iv (p3);
		glVertex2iv (p4);
		glVertex2iv (p5);
		glVertex2iv (p1);
		glVertex2iv (p6);
		glVertex2iv (p7);
		glVertex2iv (p8);
		glVertex2iv (p9);
		glVertex2iv (p10);
		glVertex2iv (p1);
	}
	glFlush();
	
    glEnd();
}       

   
void display(void)
{  
	int i;
    glPointSize(10); // sets the size of points to be drawn (in pixels)
    glMatrixMode(GL_PROJECTION);// sets the current matrix to projection
    glLoadIdentity();//multiply the current matrix by identity matrix
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);//sets the parallel(orthographic) projection of the full frame buffer 
	Draw();
	glColor3f(100.0,0.0,0.0); // sets the current drawing color to blue 
	if(check){      
	    glBegin(GL_POINTS); // writes pixels on the frame buffer with the current drawing color
	    glVertex2i(p.x,p.y);   // sets vertex
	    for(i=0;i<=pleyres;i++){
	    	glColor3f(0.0,10.0,2.0); // sets the current drawing (foreground) color to blue
	    	glVertex2i(V[i].x,V[i].y);   // sets vertex
		}	
  glEnd();
}
    glFlush();     // flushes the frame buffer to the screen
}


void Resize(int w, int h)
{
    // define the visible area of the window ( in pixels )
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
}



int cn_PnPoly( Point2D p, Point2D V[], int n)	//n oi pleyres
{
    int    cn = 0;    // the  crossing number counter
	int i;
	V[n].x=V[0].x;
	V[n].y=V[0].y;
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

int isLeft( Point2D P0, Point2D P1, Point2D P2 )	//computing if a point P1 is left of P2 or not
{
    return ( (P1.x - P0.x) * (P2.y - P0.y)
            - (P2.x -  P0.x) * (P1.y - P0.y) );
}

int wn_PnPoly( Point2D p, Point2D V[], int n )
{
    int    wn = 0;    // the  winding number counter
    V[n].x=V[0].x;
	V[n].y=V[0].y;
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

}
void mouse(int button, int state, int mousex, int mousey)
{
	int i;
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
       check=true; 
	   if(click_count<pleyres){
       V[click_count].x=mousex;
       V[click_count].y=480-mousey;
       click_count++;
   		}
   		for(i=0;i<click_count;i++){
   			printf("\nPolygon: x: %f  y: %f",V[i].x,V[i].y);
		   }
		printf("\n");
		if(click_count>=pleyres){
    	p.x = mousex;
        p.y = 480-mousey;
        r=20;
        g=0;
        b=0;
    printf("\nYour point is %f %f\n",p.x,p.y);
	
	int value;
	if(chose==1){
	
		value=cn_PnPoly( p, V, pleyres);
		if(value==0){
			printf("\nCN:The point is outside the polygon\n");
		}
		else{
			printf("\nCN:The point is inside the polygon\n");
		}
	}
	else{
	value=wn_PnPoly( p, V, pleyres);
		if(value==0){
			printf("WN:The point is outside the polygon\n");
		}
		else{
			printf("WN:The point is inside the polygon\n");
		}
        }
    }
}
	glutPostRedisplay();
     }
     
int main(int argc, char* argv[])
{
	int i;
    // initialize GLUT library state    
    glutInit(&argc, argv);
  
    // Define the main window size and initial position
    // ( upper left corner, boundaries included )
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(50, 50);

    // Create and label the main window
    glutInitDisplayMode(GLUT_RGBA | GLUT_RGB);//creates a single frame buffer of RGB color capacity.
	glutCreateWindow("Point in Polygon");//creates the window as specified by the user as above.
    // Configure various properties of the OpenGL rendering context
    Setup();

    // Callbacks for the GL and GLUT events:

    // The rendering function
    
    glutReshapeFunc(Resize);
        
    glClearColor(1, 1, 1, 0); // sets the backgraound color to white light
    glClear(GL_COLOR_BUFFER_BIT); // clears the frame buffer and set values defined in glClearColor() function call 
	
    glutDisplayFunc(display);//links the display event with the display event handler(display)
    
    glutMouseFunc(mouse);//keyboard event handler
    
    printf("\nHow many sides? Please 3-10\n");
    scanf("%d",&pleyres);
    
    printf("\nWhat method do you want,Cn or Wn ? (1/2)\n");
    scanf("%d",&chose);
    
    printf("please give the point you want(x,y)\n");
    
    //Enter main event handling loop
    glutMainLoop();
    return 0;


}
