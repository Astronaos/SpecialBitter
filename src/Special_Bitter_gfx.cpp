#include <SpecialBitter.hpp>
#include <sstream>

std::vector<PAIR<double> > g_vRounded_Rectangle_TL;
std::vector<PAIR<double> > g_vRounded_Rectangle_TR;
std::vector<PAIR<double> > g_vRounded_Rectangle_BR;
std::vector<PAIR<double> > g_vRounded_Rectangle_BL;
std::vector<PAIR<double> > g_vEllipse;
GLuint i_uiFilled_RR_List = 0;
GLuint i_uiOutline_RR_List = 0;

void Draw_Rounded_Rectangle(bool i_bFilled)
{
	double	dEdge_Radius = 0.20;
	double	dEdge_Center = 0.50 - dEdge_Radius;
	if (g_vRounded_Rectangle_TL.empty())
	{
		PAIR<double> pOffset(-dEdge_Center,dEdge_Center);
		GenerateArc(dEdge_Radius,dEdge_Radius,90.0,180.0,g_vRounded_Rectangle_TL);
		for (std::vector<PAIR<double> >::iterator cI = g_vRounded_Rectangle_TL.begin(); cI != g_vRounded_Rectangle_TL.end(); cI++)
		{
			cI[0] += pOffset;
		}
	}
	if (g_vRounded_Rectangle_TR.empty())
	{
		PAIR<double> pOffset(dEdge_Center,dEdge_Center);
		GenerateArc(dEdge_Radius,dEdge_Radius,0.0,90.0,g_vRounded_Rectangle_TR);
		for (std::vector<PAIR<double> >::iterator cI = g_vRounded_Rectangle_TR.begin(); cI != g_vRounded_Rectangle_TR.end(); cI++)
		{
			cI[0] += pOffset;
		}
	}
	if (g_vRounded_Rectangle_BR.empty())
	{
		PAIR<double> pOffset(dEdge_Center,-dEdge_Center);
		GenerateArc(dEdge_Radius,dEdge_Radius,270.0,0.0,g_vRounded_Rectangle_BR);
		for (std::vector<PAIR<double> >::iterator cI = g_vRounded_Rectangle_BR.begin(); cI != g_vRounded_Rectangle_BR.end(); cI++)
		{
			cI[0] += pOffset;
		}
	}
	if (g_vRounded_Rectangle_BL.empty())
	{
		PAIR<double> pOffset(-dEdge_Center,-dEdge_Center);
		GenerateArc(dEdge_Radius,dEdge_Radius,180.0,270.0,g_vRounded_Rectangle_BL);
		for (std::vector<PAIR<double> >::iterator cI = g_vRounded_Rectangle_BL.begin(); cI != g_vRounded_Rectangle_BL.end(); cI++)
		{
			cI[0] += pOffset;
		}
	}
	if (i_uiFilled_RR_List == 0)
	{
		i_uiFilled_RR_List = glGenLists(1);
		glNewList(i_uiFilled_RR_List,GL_COMPILE);
		glBegin(GL_TRIANGLE_FAN);
			glVertex2d(0.0,0.0);
			glVertexList(g_vRounded_Rectangle_TL);
			glVertexList(g_vRounded_Rectangle_TR);
			glVertexList(g_vRounded_Rectangle_BR);
			glVertexList(g_vRounded_Rectangle_BL);
			g_vRounded_Rectangle_TL[0].glVertex();
		glEnd();
		glEndList();
	}
	if (i_uiOutline_RR_List == 0)
	{
		i_uiOutline_RR_List = glGenLists(1);
		glNewList(i_uiOutline_RR_List,GL_COMPILE);
		glBegin(GL_LINE_LOOP);
			glVertexList(g_vRounded_Rectangle_TL);
			glVertexList(g_vRounded_Rectangle_TR);
			glVertexList(g_vRounded_Rectangle_BR);
			glVertexList(g_vRounded_Rectangle_BL);
		glEnd();
		glEndList();
	}

	if (i_bFilled && i_uiFilled_RR_List != 0)
	{
		glPushMatrix();
            glTranslated(0.5,-0.5,0.0);
		glCallList(i_uiFilled_RR_List);
        glPopMatrix();
	}
	else if (!i_bFilled && i_uiOutline_RR_List != 0)
	{
		glPushMatrix();
            glTranslated(0.5,-0.5,0.0);
		glCallList(i_uiOutline_RR_List);
        glPopMatrix();
	}
	else
	{
		glPushMatrix();
            glTranslated(1.0,-0.5,0.0);
			if (!i_bFilled)
				glLineWidth(2.0);
			glBegin(i_bFilled ? GL_TRIANGLE_FAN : GL_LINE_LOOP);
				if (i_bFilled)
					glVertex2d(0.0,0.0);
	//			glTranslated(-0.95, 0.95,0.0);
				glVertexList(g_vRounded_Rectangle_TL);
	//			glTranslated( 1.90, 0.00,0.0);
				glVertexList(g_vRounded_Rectangle_TR);
	//			glTranslated( 0.00, 1.90,0.0);
				glVertexList(g_vRounded_Rectangle_BR);
	//			glTranslated(-1.90, 0.00,0.0);
				glVertexList(g_vRounded_Rectangle_BL);
	//			glTranslated( 0.00,-1.90,0.0);
				if (i_bFilled)
					g_vRounded_Rectangle_TL[0].glVertex();
			glEnd();
		glPopMatrix();
	}
}
void Draw_Rounded_Rectangle_Button(bool i_bPressed, bool i_bActive)
{
	glPushMatrix();
		glColor4d(0.0,0.0,0.0,0.25);
		if (i_bPressed)
			glTranslated(0.02,-0.04,0.0);
		else
			glTranslated(0.10,-0.20,0.0);
		Draw_Rounded_Rectangle(true);
	glPopMatrix();

	if (i_bActive)
		glColor4d(0.0,1.0,0.0,1.0); // green
	else
		glColor4d(0.0,0.1,0.0,1.0); // green

	Draw_Rounded_Rectangle(true);
	glColor4d(0.0,0.0,0.0,1.0);
	glLineWidth(2.0);
	Draw_Rounded_Rectangle(false);
}
enum SB_DIRECTION {SBD_UP,SBD_DOWN,SBD_LEFT,SBD_RIGHT};

void Draw_Scroll_Button(SB_DIRECTION i_eDirection, bool i_bActive)
{
	glColor4d(0.75,0.75,0.75,1.0);
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
		glVertex2d(0.00,0.00);
		glVertex2d(1.0,0.00);
		glVertex2d(1.0,-1.0);
		glVertex2d(0.00,-1.0);
	glEnd();
	if (i_bActive)
		glBegin(GL_TRIANGLES);
	else
		glBegin(GL_LINE_STRIP);

		switch (i_eDirection)
		{
		case SBD_UP:
			glVertex2d(0.0,-1.0);
			glVertex2d(0.5,0.00);
			glVertex2d(1.0,-1.0);
			break;
		case SBD_DOWN:
			glVertex2d(1.0,0.0);
			glVertex2d(0.5,-1.00);
			glVertex2d(0.0,0.0);
			break;
		case SBD_LEFT:
			glVertex2d(1.0,-1.0);
			glVertex2d(0.0,-0.5);
			glVertex2d(1.0, 0.0);
			break;
		case SBD_RIGHT:
			glVertex2d(0.0, 0.0);
			glVertex2d(1.0,-0.5);
			glVertex2d(0.0,-1.0);
			break;
		}
	glEnd();
}
void Draw_Simple_Button(bool bStatus)
{
    glColor4d(0.0,0.25,0.0,1.0);
    glBegin(GL_QUADS);
        glVertex2d(0.0,0.0);
        glVertex2d(1.0,0.0);
        glVertex2d(1.0,-1.0);
        glVertex2d(0.0,-1.0);
    glEnd();
    if (bStatus)
    {
        glColor4d(0.0,1.0,0.0,1.0);
        glLineWidth(2.5);
    }
    else
    {
        glColor4d(0.0,0.0,0.0,1.0);
        glLineWidth(1.0);
    }
    glBegin(GL_LINE_LOOP);
        glVertex2d(0.0,0.0);
        glVertex2d(1.0,0.0);
        glVertex2d(1.0,-1.0);
        glVertex2d(0.0,-1.0);
    glEnd();

}
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
	if (g_vEllipse.empty())
	{
		GenerateEllipse(1.0,1.0,g_vEllipse);
	}
	if (i_idPane == m_idPane)
	{
		m_ihmMap.Draw_Map(NULL);
		glColor4d(0.0,0.0,0.0,1.0);
		glLineWidth(2.25);
		//@@TODO: figure out why depth testing is doing funny things.  depth testing will help with making sure grid lines are underneath units
		glTranslated(0.0,0.0,0.0025); // draw grid slightly above map but below units
		m_ihmMap.Draw_Grid();
		double dSize = Get_Pane_Aspect_Ratio(m_idPane);
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
