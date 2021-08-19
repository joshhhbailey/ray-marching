/// \brief Stores mouse and window parameters
/// \author Josh Bailey
/// \date 19/08/21 Updated to NCCA Coding standard

#ifndef WINDOWPARAMS_H_
#define WINDOWPARAMS_H_

struct WinParams
{
  int m_mouseXPos = 0;
  int m_mouseYPos = 0;
  int m_winWidth = 1024;
  int m_winHeight = 720;
};

#endif // _WINDOWPARAMS_H_