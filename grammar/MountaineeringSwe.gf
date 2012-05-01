--# -path=.:present:alltenses

concrete MountaineeringSwe of Mountaineering = PhrasebookSwe **
    MountaineeringI with 
      (Syntax = SyntaxSwe),
      (Symbolic = SymbolicSwe),
      (Lexicon = LexiconSwe) **
	open
	  SyntaxSwe,
	  ParadigmsSwe,
	  (L = LexiconSwe),
	  IrregSwe,
	  ExtraSwe,
	  Prelude in {    
  lin
    HoldPlaceKind x = mkCNPlace x (mkPrep "vid") to_Prep;

-- Words
  lin
    BelayStation = mkPlace (mkN "standplats") "p�";
    Cliff = mkPlace (mkN "klippa") "p�";
    ClimbingGym = mkPlace (mkN "kl�ttergym" neutrum) "p�";
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
    
    Ascender = mkCN (mkN "repkl�mma");
    Bolt = mkCN (mkN "bult");
    Carabiner = mkCN (mkN "karbinhake");
    Chalk = mkCN (mkN "krita");
    ChestHarness = mkCN (mkN "br�stsele" "br�stselar");
    ClimbingShoe = mkCN (mkN "kl�ttersko" "kl�tterskor");
    Cord = mkCN (mkN "sn�re" neutrum);
    Crampon = mkCN (mkN "stegj�rn" neutrum);
    ExpansionBolt = mkCN (mkN "borrbult");
    Harness = mkCN (mkN "sele" "selar");
    Helmet = mkCN (mkN "hj�lm");
    IceAxe = mkCN (mkN "isyxa");
    Jumar = mkCN (mkN "jumar" "jumars");
    LockingCarabiner = mkCN (mkN "l�skarbin" "l�skarbiner");
    Nut = mkCN (mkN "kil");
    Piton = mkCN (mkN "kil");
    Rack = mkCN (mkN "utrustning");
    Ring = mkCN (mkN "ring");
    Rope = mkCN (mkN "rep");
    Runner, Sling = mkCN (mkN "slinga");
    Webbing = mkCN (mkN "nylonband" neutrum);
    
    Bucket, Jug = mkCN (mkN "brevl�da");
    Crack = mkCN (mkN "spricka");
    NHold = mkCN (mkN "grepp");
    Pocket = mkCN (mkN "pocket" "pocketen" "pockets" "pocketsarna");
    Sloper = mkCN (mkN "slope" "slopes");
    
    Bowline = mkCN (mkN "p�lstek");
    ButterflyKnot = mkCN (mkN "fj�rilsstek");
    DoubleFisherman = mkCN (mkN "dubbel fiskarknop" "dubbla fiskarknopen" "dubbla fiskarknopar" "dubbla fiskarknoparna");
    FigureOfEightKnot = mkCN (mkN "�tta");
    FishermansKnot = mkCN (mkN "fiskarknop");
    Knot = mkCN (mkN "knop");
    OverhandBend = mkCN (mkN "dubbel �verhandsknop" "dubbla �verhandsknopen" "dubbla �verhandsknopar" "dubbla �verhandsknoparna");
    OverhandKnot = mkCN (mkN "�verhandsknop");
    PrusikKnot = mkCN (mkN "prusik");
    WaterKnot = mkCN (mkN "vattenknop");
}
