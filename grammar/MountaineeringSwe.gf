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
    BelayStation = mkPlace (mkN "standplats") "p�";
    Cliff = mkPlace (mkN "klippa") "p�";
    Glacier = mkPlace (mkN "glaci�r") "p�";
    Mountain = mkPlace L.mountain_N "p�";
    Overhang = mkPlace (mkN "�verh�ng" neutrum) "i";
    Summit = mkPlace (mkN "topp") "p�";
    
    VAbseil, VRappel = mkVP (regV "fira");
    VBelay = mkVP (regV "s�kra");
    VBoulder = mkVP (regV "bouldra");
    VClimb = mkVP (regV "kl�ttra");
    VFall = mkVP (regV "falla");
    VLead = mkVP (regV "leda");
    VStem = mkVP (regV "st�mma");
    
    GBelayOn = mkGreeting "s�kring klar";
    GBelow, GRock = mkGreeting "sten";
    GClimbing = mkGreeting "jag kl�ttrar";
    GFalling = mkGreeting "faller";
    GOffBelay, GSafe = mkGreeting "l�gg av";
    GRope = mkGreeting "rep";
    GSlack = mkGreeting "rep";
    GUpRope = mkGreeting "tag hem";
}
