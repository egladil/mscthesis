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
    BelayStation = mkPlace (mkN "standplats") "på";
    Cliff = mkPlace (mkN "klippa") "på";
    Glacier = mkPlace (mkN "glaciär") "på";
    Mountain = mkPlace L.mountain_N "på";
    Overhang = mkPlace (mkN "överhäng" neutrum) "i";
    Summit = mkPlace (mkN "topp") "på";
    
    VAbseil, VRappel = mkVP (regV "fira");
    VBelay = mkVP (regV "säkra");
    VBoulder = mkVP (regV "bouldra");
    VClimb = mkVP (regV "klättra");
    VFall = mkVP (regV "falla");
    VLead = mkVP (regV "leda");
    VStem = mkVP (regV "stämma");
    
    GBelayOn = mkGreeting "säkring klar";
    GBelow, GRock = mkGreeting "sten";
    GClimbing = mkGreeting "jag klättrar";
    GFalling = mkGreeting "faller";
    GOffBelay, GSafe = mkGreeting "lägg av";
    GRope = mkGreeting "rep";
    GSlack = mkGreeting "rep";
    GUpRope = mkGreeting "tag hem";
}
