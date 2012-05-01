--# -path=.:present:alltenses

concrete MountaineeringEng of Mountaineering = PhrasebookEng **
    MountaineeringI with 
      (Syntax = SyntaxEng),
      (Symbolic = SymbolicEng),
      (Lexicon = LexiconEng) **
    open 
      SyntaxEng, 
      ParadigmsEng, 
      (L = LexiconEng), 
      (P = ParadigmsEng), 
      IrregEng, 
      ExtraEng, 
      Prelude in {    
  lin
    HoldToPlaceKind x = mkCNPlace x (mkPrep "by") to_Prep;

-- Words
  lin
    BelayStation = mkPlace "belay station" "at";
    Cliff = mkPlace "cliff" "on";
    ClimbingGym = mkPlace "climbing gym" "at";
    Glacier = mkPlace "glacier" "on";
    Mountain = mkPlace "mountain" "on";
    Overhang = mkPlace "overhang" "in";
    Summit = mkPlace "summit" "at";
    
    VAbseil = mkVP (regV "abseil");
    VBelay = mkVP (regV "belay");
    VBoulder = mkVP (regV "boulder");
    VClimb = mkVP (regV "climb");
    VFall = mkVP (regV "fall");
    VLead = mkVP (regV "lead");
    VRappel = mkVP (regV "rappel");
    VStem = mkVP (regV "stem");
    
    GBelayOn = mkGreeting "belay on";
    GBelow = mkGreeting "below";
    GClimbing = mkGreeting "climbing";
    GFalling = mkGreeting "falling";
    GOffBelay = mkGreeting "off belay";
    GRock = mkGreeting "rock";
    GRope = mkGreeting "rope";
    GSafe = mkGreeting "safe";
    GSlack = mkGreeting "slack";
    GUpRope = mkGreeting "up rope";
    
    Ascender = mkCN (mkN "ascender");
    Bolt = mkCN (mkN "bolt");
    Carabiner = mkCN (mkN "carabiner");
    Chalk = mkCN (mkN "chalk");
    ChestHarness = mkCN (mkN "chest harness");
    ClimbingShoe = mkCN (mkN "climbing shoe");
    Cord = mkCN (mkN "cord");
    Crampon = mkCN (mkN "crampon");
    ExpansionBolt = mkCN (mkN "expansion bolt");
    HalfRope = mkCN (mkN "half rope");
    Harness = mkCN (mkN "harness");
    Helmet = mkCN (mkN "helmet");
    IceAxe = mkCN (mkN "ice axe");
    Jumar = mkCN (mkN "jumar");
    LockingCarabiner = mkCN (mkN "locking biner");
    Nut = mkCN (mkN "nut");
    Piton = mkCN (mkN "piton");
    Rack = mkCN (mkN "rack");
    Ring = mkCN (mkN "ring");
    Rope = mkCN (mkN "rope");
    Runner = mkCN (mkN "runner");
    Sling = mkCN (mkN "sling");
    Webbing = mkCN (mkN "webbing");
    
    Bucket = mkCN (mkN "bucket");
    Chickenhead = mkCN (mkN "chickenhead");
    ChippedHold = mkCN (mkN "chipped hold");
    Crack = mkCN (mkN "crack");
    Hold = mkCN (mkN "hold");
    Jug = mkCN (mkN "jug");
    Pocket = mkCN (mkN "pocket");
    Sidepull = mkCN (mkN "sidepull");
    Sloper = mkCN (mkN "sloper");
    Undercling = mkCN (mkN "undercling");
    
    Bowline = mkCN (mkN "bowline");
    ButterflyKnot = mkCN (mkN "butterfly knot");
    DoubleFisherman = mkCN (mkN "double fisherman's knot");
    FigureOfEightKnot = mkCN (mkN "figure of eight");
    FishermansKnot = mkCN (mkN "fisherman's knot");
    Knot = mkCN (mkN "knot");
    MunterHitch = mkCN (mkN "munter hitch");
    OverhandBend = mkCN (mkN "overhand bend");
    OverhandKnot = mkCN (mkN "overhand knot");
    PrusikKnot = mkCN (mkN "prusik");
    ThreadedOverhandKnot = mkCN (mkN "threaded overhand knot");
    WaterKnot = mkCN (mkN "water knot");
}
