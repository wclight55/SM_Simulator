
#ifndef ProjectModelH
#define ProjectModelH
#include <msxmldom.hpp>
#include <XMLDoc.hpp>
#include <xmldom.hpp>
#include <XMLIntf.hpp>
#include "LineEvent.h"
#include "NodeEvent.h"
#include "WalkingUser.h"
class ProjectModel:public TObject
{
public:
    TXMLDocument* XMLDoc;
	public:
		String m_strProjectName;
		String m_strProjectAuthor;
		String m_strProjectTime;
		String m_strProjectDiscription;

		long m_nMaxRuleSetID;
    long m_nMaxLineID;
    TList* m_pFCMsNodeList;
    TList* m_pLineEventList;

    TDrawingTool DrawingType;//
	public:
		ProjectModel();
		virtual __fastcall ~ProjectModel();
    void ClearNodeList();

};

#endif
