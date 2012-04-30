--# -path=.:present:alltenses

concrete MountaineeringSwe of Mountaineering = PhrasebookSwe ** 
	open
	  SyntaxSwe,
	  ParadigmsSwe,
	  (L = LexiconSwe),
	  IrregSwe,
	  ExtraSwe,
	  Prelude in {

  lin
    Mountain = mkPlace L.mountain_N "p�";
    Overhang = mkPlace (mkN "�verh�ng" neutrum) "i";
    Summit = mkPlace (mkN "topp") "p�";
    
    GBelayOn = mkGreeting "s�kring klar";
    GBelow, GRock = mkGreeting "sten";
    GFalling = mkGreeting "faller";
    GOffBelay, GSafe = mkGreeting "l�gg av";
    GRope = mkGreeting "rep";
    GSlack = mkGreeting "rep";
    GUpRope = mkGreeting "tag hem";
}
