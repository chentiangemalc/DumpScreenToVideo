#include <vfw.h>
#include <String>
#define TEXT_HEIGHT	20
#define AVIIF_KEYFRAME	0x00000010L // this frame is a key frame.
#define BUFSIZE 260

#pragma comment(lib,"Vfw32.lib")
class CAVIFile 
{
public:
	CAVIFile(LPWSTR lpFileName, int xdim = -1, int ydim = -1);
	virtual ~CAVIFile();

	virtual bool AddFrame(HBITMAP& bmp);
	std::wstring GetFName() const             {return FName;};
	virtual bool IsOK() const            {return bOK;};

private:
	std::wstring FName;
	int xDim;
	int yDim;

	AVISTREAMINFO strhdr;
	PAVIFILE pfile;
	PAVISTREAM ps;
	PAVISTREAM psCompressed;
	PAVISTREAM psText;
	AVICOMPRESSOPTIONS opts;
	AVICOMPRESSOPTIONS FAR * aopts[1];
	DWORD dwTextFormat;
	char szText[BUFSIZE];
	int nFrames;
	bool bOK;
};

