#include "3Dshape.h"
#include "Line.h"


void _3Dshape::draw() {
	double crossl = calDistance(points[0], points[1]);
	int l = crossl / sqrt(3);
	 
	pixel A, B, C, D, E, F, G, H;
	A = points[0];
	B = { A.x + l,A.y };
	C = { A.x + l,A.y + l };
	D = { A.x,A.y + l };
	E = points[1];
	F = { E.x,E.y - l };
	G = { E.x - l,E.y - l };
	H = { E.x - l,E.y };

	Line AB(A, B, lineColor);
	AB.draw();
	Line BC(B, C, lineColor);
	BC.draw();
	Line CD(C, D, lineColor);
	CD.draw();
	Line DA(D, A, lineColor);
	DA.draw();
	Line EF(E, F, lineColor);
	
	Line FG(F, G, lineColor);
	
	Line GH(G, H, lineColor);
	
	Line HE(H, E, lineColor);
	
	Line AG(A, G, lineColor);
	
	Line BF(B, F, lineColor);
	
	Line CE(C, E, lineColor);
	
	Line DH(D, H, lineColor);
	
	if (G.x > A.x && G.y > A.y) {
		HE.draw();
		EF.draw();
		BF.draw();
		CE.draw();
		DH.draw();
	}
	else if (F.x<B.x && F.y>B.y) {
		GH.draw();
		HE.draw();
		AG.draw();
		CE.draw();
		DH.draw();
	}
	else if (H.x > D.x && H.y < D.y) {
		EF.draw();
		FG.draw();
		AG.draw();
		BF.draw();
		CE.draw();
	}
	else if (E.x < C.x && E.y < C.y) {
		FG.draw();
		GH.draw();
		AG.draw();
		BF.draw();
		DH.draw();
	}
	/*
	EF.draw();
	FG.draw();
	GH.draw();
	HE.draw();
	AG.draw();
	BF.draw();
	CE.draw();
	DH.draw();
	*/
}


bool _3Dshape::isSelect(pixel p) {
	int xmin = min(points[0].x, points[1].x);
	int ymin = min(points[0].y, points[1].y);
	int xmax = max(points[0].x, points[1].x);
	int ymax = max(points[0].y, points[1].y);

	if (p.x<xmin || p.x>xmax || p.y<ymin || p.y>ymax) {
		return false;
	}

	return true;
}