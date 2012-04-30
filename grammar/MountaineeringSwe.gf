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
    Mountain = mkPlace L.mountain_N "på";
    Overhang = mkPlace (mkN "överhäng" neutrum) "i";
    Summit = mkPlace (mkN "topp") "på";
    
    GBelayOn = mkGreeting "säkring klar";
    GBelow, GRock = mkGreeting "sten";
    GFalling = mkGreeting "faller";
    GOffBelay, GSafe = mkGreeting "lägg av";
    GRope = mkGreeting "rep";
    GSlack = mkGreeting "rep";
    GUpRope = mkGreeting "tag hem";
}
