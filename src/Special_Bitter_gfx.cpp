#include <SpecialBitter.hpp>
#include <sstream>

void SPECIAL_BITTER_MAIN::gfx_init(void) // initialization routine; rendering context already created
{
	glClearColor(1.0,1.0,1.0,0.0);
	glShadeModel(GL_SMOOTH);
	glMaterialf(GL_FRONT,GL_SPECULAR,10.0);
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	SelectFontFace(SANS,true,false);
}
void SPECIAL_BITTER_MAIN::gfx_reshape(const PAIR<unsigned int> & i_tNew_Size) // window size change
{
	// set basic projection
	PAIR<unsigned int> m_tViewport_Size = i_tNew_Size;
	glViewport(0,0,(GLsizei) m_tViewport_Size.m_tX, (GLsizei) m_tViewport_Size.m_tY);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	glOrtho(0.0,m_tViewport_Size.m_tX / m_tViewport_Size.m_tY,0.0,1.0,0.0,1.0);
	glFrustum(0.0,m_tViewport_Size.m_tX / m_tViewport_Size.m_tY,0.0,1.0,0.0,1.0);
	glMatrixMode(GL_MODELVIEW);

	// make the main pane to be the full window
	PAIR<unsigned int> tWindow_BL(0,0);
	PAIR<unsigned int> tWindow_TR((unsigned int)m_tViewport_Size.m_tX,(unsigned int)(m_tViewport_Size.m_tY));

	Move_Pane(m_idPane,QUAD<unsigned int> (tWindow_BL,tWindow_TR));

	// define buttons within the pane
	m_mMain_Pane_Buttons[BLUE_CIRCLE_SELECT] = BUTTON_INFO(BUTTON_INFO::RECTANGLE, PAIR<double>(1.0,0.8), PAIR<double>(0.1,0.05), BLUE_CIRCLE_SELECT);
}
void SPECIAL_BITTER_MAIN::gfx_close(void) // graphics exiting; rendering context still active
{
}

void SPECIAL_BITTER_MAIN::gfx_display(pane_id i_idPane) // primary display routine
{
	if (i_idPane == m_idPane)
	{
		double dSize = Get_Pane_Aspect_Ratio(m_idPane);
		// replace the 
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-dSize * 0.5,dSize * 0.5,-0.5,0.5,0.001,0.20);
//		glOrtho(-dSize,dSize,-0.5,0.5,1.5,20.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glEnable(GL_DEPTH_TEST);
		glTranslated(0.0,0.0,-0.05);
		//m_ihmMap.Draw_Map(NULL);
//		glColor4d(0.0,0.0,0.0,1.0);
		glLineWidth(2.25);
		//@@TODO: figure out why depth testing is doing funny things.  depth testing will help with making sure grid lines are underneath units
//		glTranslated(0.0,0.0,0.0025); // draw grid slightly above map but below units
		m_ihmMap.Draw_Grid();
//		glTranslated(dSize*0.5,0.5,0.0);
//		glScaled(1.0,1.0,-1.0);
		glRotated(m_ihmMap.Get_Isometric_Camera_Angle(),1.0,0.0,0.0);
		glRotated(m_ihmMap.Get_Camera_Rotation_Angle(),0.0,0.0,1.0);
		glColor4d(1.0,0.0,0.0,1.0);
		glBegin(GL_LINES);
			glVertex3d(0.0,0.0,0.0);
			glVertex3d(1.0,0.0,0.0);
		glEnd();
		glColor4d(0.0,1.0,0.0,1.0);
		glBegin(GL_LINES);
			glVertex3d(0.0,0.0,0.0);
			glVertex3d(0.0,1.0,0.0);
		glEnd();
		glColor4d(0.0,0.0,1.0,1.0);
		glBegin(GL_LINES);
			glVertex3d(0.0,0.0,0.0);
			glVertex3d(0.0,0.0,1.0);
		glEnd();

/*		glColor4d(1.0,0.00,0.0,1.0);
		glBegin(GL_TRIANGLES);
			// top
			glVertex3d( 0.05,-0.05,0.00);
			glVertex3d(-0.05,-0.05,0.00);
			glVertex3d( 0.05, 0.05,0.00);
//			glVertex3d(-0.05, 0.05,0.05);

		glEnd();*/
		glColor4d(0.0,1.00,0.0,1.0);
		glBegin(GL_QUADS);
			// top
			glVertex3d(-0.05,-0.05,0.00);
			glVertex3d(-0.05,0.05,0.00);
			glVertex3d(-0.05,0.05,0.05);
			glVertex3d(-0.05,-0.05,0.05);
		glEnd();
		glColor4d(0.0,0.00,1.0,1.0);
		glBegin(GL_QUADS);
			// top
			glVertex3d( 0.05,-0.05,0.00);
			glVertex3d( 0.05,0.05,0.00);
			glVertex3d( 0.05,0.05,0.05);
			glVertex3d( 0.05,-0.05,0.05);
		glEnd();
		glColor4d(1.0,1.00,0.0,1.0);
		glBegin(GL_QUADS);
			// top
			glVertex3d(-0.05,-0.05,0.00);
			glVertex3d( 0.05,-0.05,0.00);
			glVertex3d( 0.05,-0.05,0.05);
			glVertex3d(-0.05,-0.05,0.05);
		glEnd();
		glColor4d(0.0,1.00,1.0,1.0);
		glBegin(GL_QUADS);
			// top
			glVertex3d(-0.05, 0.05,0.00);
			glVertex3d( 0.05, 0.05,0.00);
			glVertex3d( 0.05, 0.05,0.05);
			glVertex3d(-0.05, 0.05,0.05);
		glEnd();
		glColor4d(0.0,0.0,0.0,1.0);
		glBegin(GL_LINES);
			glVertex3d(-0.05, 0.05,0.00);
			glVertex3d(-0.05, 0.05,0.05);
			glVertex3d( 0.05, 0.05,0.00);
			glVertex3d( 0.05, 0.05,0.05);
			glVertex3d(-0.05,-0.05,0.00);
			glVertex3d(-0.05,-0.05,0.05);
			glVertex3d( 0.05,-0.05,0.00);
			glVertex3d( 0.05,-0.05,0.05);
		glEnd();
// second
/*		glColor4d(1.0,0.0,1.0,1.0);
		glBegin(GL_QUADS);
			// top
			glVertex3d(-0.025,-0.025,0.10);
			glVertex3d(-0.025,0.025,0.10);
			glVertex3d(0.025,0.025,0.10);
			glVertex3d(0.025,-0.025,0.10);
			// top
			glVertex3d(-0.025,-0.025,0.05);
			glVertex3d(-0.025,0.025,0.05);
			glVertex3d(-0.025,0.025,0.10);
			glVertex3d(-0.025,-0.025,0.10);
			// top
			glVertex3d( 0.025,-0.025,0.05);
			glVertex3d( 0.025,0.025,0.05);
			glVertex3d( 0.025,0.025,0.10);
			glVertex3d( 0.025,-0.025,0.10);
			// top
			glVertex3d(-0.025,-0.025,0.05);
			glVertex3d( 0.025,-0.025,0.05);
			glVertex3d( 0.025,-0.025,0.10);
			glVertex3d(-0.025,-0.025,0.10);
			// top
			glVertex3d(-0.025, 0.025,0.05);
			glVertex3d( 0.025, 0.025,0.05);
			glVertex3d( 0.025, 0.025,0.10);
			glVertex3d(-0.025, 0.025,0.10);


		glEnd();
*/		glDisable(GL_DEPTH_TEST);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0,dSize,0.0,1.0,0.0,1.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
//		glColor4d(0.5,0.5,0.5,1.0);
//		glBegin(GL_QUADS);
//			glVertex2d(0.0,0.3);
//			glVertex2d(dSize,0.3);
//			glVertex2d(dSize,0.0);
//			glVertex2d(0.0,0.0);
//		glEnd();

		// draw a blue circle with radius (0.01), set at x = sin(t), y = cos(t)
		glColor4d(0.0,0.0,1.0,1.0);
		glPushMatrix();
			glTranslated(0.5,0.5,0.0);
			glScaled(0.5,0.5,0.5);
			glTranslated(sin(m_dTimer),cos(m_dTimer),0.0);
			glScaled(0.01,0.01,0.01);
			glBegin(GL_TRIANGLE_FAN);
				glVertex3d(0,0,0);
				glVertexList(g_vEllipse);
			glEnd();	
		glPopMatrix();
		// loop through list of buttons, drawing each one
		for (std::map<button_id,BUTTON_INFO>::const_iterator cI = m_mMain_Pane_Buttons.begin(); cI != m_mMain_Pane_Buttons.end(); cI++)
		{
			PAIR<double> pdPosition = cI->second.GetPosition();
			PAIR<double> pdSize = cI->second.GetSize();

			glPushMatrix();
				glTranslated(pdPosition.m_tX,pdPosition.m_tY,0.0);
				glScaled(pdSize.m_tX,pdSize.m_tY,1.0);
				int iStatus = cI->second.GetStatus();
				switch (cI->second.GetID())
				{
				case BLUE_CIRCLE_SELECT:
					glColor4d(0,0,0,1.0);
					glBegin(GL_LINE_STRIP);
						glVertex3d(0.0,0.0,0.0);
						glVertex3d(0.0,-1.0,0.0);
						glVertex3d(1.0,-1.0,0.0);
						glVertex3d(1.0,0.0,0.0);
						glVertex3d(0.0,0.0,0.0);
					glEnd();
					glColor4d(0.0,0.0,1.0,1.0);
					glPushMatrix();
						glTranslated(0.5,-0.5,0.0);
						glScaled(0.5,0.5,0.5);
						glBegin(GL_TRIANGLE_FAN);
							glVertex3d(0,0,0);
							glVertexList(g_vEllipse);
						glEnd();	
					glPopMatrix();
					break;
				}
			glPopMatrix();
		}
		// if the user is in the process of placing a blue circle, draw it at the current mouse position
		if (m_idSelected_Button == BLUE_CIRCLE_SELECT)
		{
			glColor4d(0.0,0.0,1.0,1.0);
			glPushMatrix();
				glTranslated(m_pdMouse_Position.m_tX,m_pdMouse_Position.m_tY,0.0);
				glScaled(0.02,0.02,0.02);
				glBegin(GL_TRIANGLE_FAN);
					glVertex3d(0,0,0);
					glVertexList(g_vEllipse);
				glEnd();	
			glPopMatrix();
		}
		// iterate through the list of placed objects, draw each one
		for (std::vector<OBJECT>::const_iterator cI = m_vPlaced_Objects.begin(); cI != m_vPlaced_Objects.end(); cI++)
		{
			switch (cI->m_eObject_Type)
			{
			case OBJECT::BLUE_CIRCLE:
				glColor4d(0.0,0.0,1.0,1.0);
				glPushMatrix();
					glTranslated(cI->m_piPosition.m_tX,cI->m_piPosition.m_tY,0.0);
					glScaled(0.02,0.02,0.02);
					glBegin(GL_TRIANGLE_FAN);
						glVertex3d(0,0,0);
						glVertexList(g_vEllipse);
					glEnd();	
				glPopMatrix();
				break;
			}
		}
		
	}
}
void SPACE::Draw_Layer(unsigned int i_uiLayer, void * io_lpvData) const
{
}
