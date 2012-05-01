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
    ClimbingGym = mkPlace (mkN "klättergym" neutrum) "på";
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
    
    Ascender = mkCN (mkN "repklämma");
    Bolt = mkCN (mkN "bult");
    Carabiner = mkCN (mkN "karbinhake");
    Chalk = mkCN (mkN "krita");
    ChestHarness = mkCN (mkN "bröstsele" "bröstselar");
    ClimbingShoe = mkCN (mkN "klättersko" "klätterskor");
    Cord = mkCN (mkN "snöre" neutrum);
    Crampon = mkCN (mkN "stegjärn" neutrum);
    ExpansionBolt = mkCN (mkN "borrbult");
    Harness = mkCN (mkN "sele" "selar");
    Helmet = mkCN (mkN "hjälm");
    IceAxe = mkCN (mkN "isyxa");
    Jumar = mkCN (mkN "jumar" "jumars");
    LockingCarabiner = mkCN (mkN "låskarbin" "låskarbiner");
    Nut = mkCN (mkN "kil");
    Piton = mkCN (mkN "kil");
    Rack = mkCN (mkN "utrustning");
    Ring = mkCN (mkN "ring");
    Rope = mkCN (mkN "rep");
    Runner, Sling = mkCN (mkN "slinga");
    Webbing = mkCN (mkN "nylonband" neutrum);
}
