#!/usr/bin/python

# This is statement is required by the build system to query build info
if __name__ == '__build__':
	raise Exception

'''

cube.py
Converted to Python by Jason Petrone 6/00

/*
 * Copyright (c) 1993-1997, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED 
 * Permission to use, copy, modify, and distribute this software for 
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that 
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission. 
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 * 
 * US Government Users Restricted Rights 
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 *
 * OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
 */

 '''

#  cube.c
#  This program demonstrates a single modeling transformation,
#  glScalef() and a single viewing transformation, gluLookAt().
#  A wireframe cube is rendered.

import sys

try:
  from OpenGL.GLUT import *
  from OpenGL.GL import *
  from OpenGL.GLU import *
except:
  print '''
ERROR: PyOpenGL not installed properly.  
        '''

def flip(v):
  result = [ 0.0, 0.0, 0.0, 0.0 ]
  for i in range(3):
    result[i] = -v[i]
  result[3] = v[3]
  return result

rotation = 0

enable0 = True
enable1 = True
enable2 = True

def init(): 
   glClearColor (0.0, 0.0, 0.0, 0.0)
   glShadeModel (GL_SMOOTH)

def display():
   ambient = [ 0.1, 0.1, 0.1, 1.0 ]
   specular = [ 1.0, 1.0, 1.0, 1.0 ]
   specular0 = [ 0.0, 0.0, 0.0, 1.0 ]
   specular1 = [ 0.0, 0.0, 0.0, 1.0 ]
   specular2 = [ 0.0, 0.0, 0.0, 1.0 ]
   diffuse0 = [ 1.0, 0.0, 0.0, 1.0 ]
   diffuse1 = [ 0.0, 1.0, 0.0, 1.0 ]
   diffuse2 = [ 0.0, 0.0, 1.0, 1.0 ]
   shininess = [ 20.0 ]
   position0 = [ 1.0, 0.0, 3.0, 1.0 ]
   position1 = [ -1.0, 0.0, 3.0, 1.0 ]
   position2 = [ 0.0, -1.0, 5.0, 1.0 ]
   cutoff = 17.0
   exponent = 3.1
   spotDirection0 = flip(position0)
   spotDirection1 = flip(position1)
   spotDirection2 = flip(position2)
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
   glEnable(GL_DEPTH_TEST)
   glEnable(GL_LIGHTING)
   if enable0:
     glEnable(GL_LIGHT0)
   else:
     glDisable(GL_LIGHT0)
   if enable1:
     glEnable(GL_LIGHT1)
   else:
     glDisable(GL_LIGHT1)
   if enable2: 
     glEnable(GL_LIGHT2)
   else:
     glDisable(GL_LIGHT2)
   glEnable(GL_NORMALIZE)
   glMaterialfv(GL_FRONT, GL_SPECULAR, specular)
   glMaterialfv(GL_FRONT, GL_SHININESS, shininess)
   glColor3f (1.0, 1.0, 1.0)
   glLoadIdentity ()             # clear the matrix 
   # viewing transformation 
   glLightfv(GL_LIGHT0, GL_POSITION, position0)
   glLightfv(GL_LIGHT1, GL_POSITION, position1)
   glLightfv(GL_LIGHT2, GL_POSITION, position2)
   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient)
   glLightfv(GL_LIGHT1, GL_AMBIENT, ambient)
   glLightfv(GL_LIGHT2, GL_AMBIENT, ambient)
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0)
   glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1)
   glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2)
   glLightfv(GL_LIGHT0, GL_SPECULAR, diffuse0)
   glLightfv(GL_LIGHT1, GL_SPECULAR, diffuse1)
   glLightfv(GL_LIGHT2, GL_SPECULAR, diffuse2)
   glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection0)
   glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection1)
   glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDirection2)
   glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, cutoff)
   glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, cutoff)
   glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, cutoff)
   glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, exponent)
   glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, exponent)
   glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, exponent)
   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)
   glScalef (1.0, 2.0, 1.0)      # modeling transformation 
   glRotated(20.0, 1.0, 0.0, 0.0)
   glRotated(rotation, 0.0, 1.0, 0.0)
   glTranslatef(0.0, -0.25, 0.0)
   glutSolidTeapot(1.0)
   glFlush ()

def reshape (w, h):
   glViewport (0, 0, w, h)
   ar = float(w)/float(h)
   print ar
   print 1/ar
   glMatrixMode (GL_PROJECTION)
   glLoadIdentity ()
   scale = ar * 0.75
   glFrustum (-scale, scale, -1.0, 1.0, 1.5, 20.0)
   glMatrixMode (GL_MODELVIEW)

def mouse(button, state, x, y):
   global rotation
   if button == GLUT_LEFT_BUTTON and state == GLUT_DOWN:
       rotation = (rotation + 20) % 360
       glutPostRedisplay()

def keyboard(key, x, y):
   global enable0
   global enable1
   global enable2
   global rotation
   if key == chr(27):
      import sys
      sys.exit(0)
   elif key == "1":
      enable0 = not enable0
   elif key == "2":
      enable1 = not enable1
   elif key == "3":
      enable2 = not enable2
   elif key == "o":
      rotation = (rotation + 10) % 360
   elif key == "p":
      rotation = (rotation - 10) % 360
   glutPostRedisplay()

glutInit(sys.argv)
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH | GLUT_ALPHA)
glutInitWindowSize (500, 500)
glutInitWindowPosition (100, 100)
glutCreateWindow ('cube')
init ()
glutDisplayFunc(display)
glutReshapeFunc(reshape)
glutMouseFunc(mouse)
glutKeyboardFunc(keyboard)
glutMainLoop()
