--# -path=.:present:alltenses

concrete MountaineeringGer of Mountaineering =
    PhrasebookGer -
      [
        ABusinessman,
        ACook,
        ADoctor,
        AEngineer,
        ALawyer,
        AProfessor,
        AStudent,
        ATeacher
      ] **
    MountaineeringI -
      [
        ADoVerbPhraseDirection,
        AModVerbPhraseDirection,
        ProTeacherFemale,
        ProPhysicianFemale
      ] with 
      (Syntax = SyntaxGer),
      (Symbolic = SymbolicGer),
      (Lexicon = LexiconGer) **
    open
      SyntaxGer,
      ParadigmsGer,
      (L = LexiconGer),
      IrregGer,
      ExtraGer,
      Prelude in {
  lin
    HoldToPlaceKind x = mkCNPlace x (mkPrep "bei" dative) zu_Prep;
    
-- Sentences
  lin
    ADoVerbPhraseDirection p vp x = prop (mkCl p.name (mkVP vp x.to)) ;
    AModVerbPhraseDirection m p vp x = prop (mkCl p.name (mkVP m (mkVP vp x.to))) ;

-- Words
  lin
    BelayStation = mkPlace (mkN "Standplatz" "Standplätze" masculine) on_Prep zu_Prep;
    Cliff = mkPlace (mkN "Fels" "Felsen" masculine) on_Prep zu_Prep;
    ClimbingGym = mkPlace (mkN "Kletterhalle" "Kletterhallen" feminine) in_Prep inAcc_Prep;
    Glacier = mkPlace (mkN "Gletscher") on_Prep zu_Prep;
    Mountain = mkPlace (L.mountain_N) on_Prep zu_Prep;
    Overhang = mkPlace (mkN "Überhang" "Überhänge" masculine) in_Prep inAcc_Prep;
    Summit = mkPlace (mkN "Gipfel") on_Prep zu_Prep;
    
    VAbseil, VRappel = mkVP (regV "abseilen");
    VBelay = mkVP (regV "sichern");
    VBoulder = mkVP (regV "bouldern");
    VClimb = mkVP (regV "klettern");
    VFall = mkVP (regV "stürzen");
    VLead = mkVP (regV "vorsteigen");
    VStem = mkVP (regV "stemmen");
    
    GBelayOn = mkGreeting "nachkommen";
    GBelow, GRock = mkGreeting "Stein";
    GClimbing = mkGreeting "komme";
    GOffBelay, GSafe = mkGreeting "stand";
    GRope = mkGreeting "Seil";
    GSlack = mkGreeting "Seil";
    GUpRope = mkGreeting "Seil ein";

    Ascender = mkCN (mkN "Steigklemme");
    Bolt = mkCN (mkN "Haken");
    Carabiner = mkCN (mkN "Karabinerhaken" "Karabinerhaken" masculine);
    Chalk = mkCN (mkN "Chalk" "Chalk" "Chalk" "Chalk" "Chalk" "Chalk" masculine);
    ChestHarness = mkCN (mkN "Brustklettergurt");
    ClimbingShoe = mkCN (mkN "Kletterschuh");
    Cord = mkCN (mkN "Reepschnur" "Reepschnüre" feminine);
    Crampon = mkCN (mkN "Steigeisen" "Steigeisen" neuter);
    ExpansionBolt = mkCN (mkN "Bohrhaken");
    HalfRope = mkCN (mkN "Halbseil" "Halbseile" neuter);
    Harness = mkCN (mkN "Klettergurt");
    Helmet = mkCN (mkN "Helm");
    IceAxe = mkCN (mkN "Eispickel" "Eispickel" masculine);
    Jumar = mkCN (mkN "Jumar");
    LockingCarabiner = mkCN (mkN "Verschlusskarabiner" "Verschlusskarabiner" masculine);
    Nut = mkCN (mkN "Klemmkeil");
    Piton = mkCN (mkN "Haken" "Haken" masculine);
    Rack = mkCN (mkN "Materialsortiment" "Materialsortimente" neuter);
    Ring = mkCN (mkN "Ring");
    Rope = mkCN (mkN "Seil" "Seile" neuter);
    Runner, Sling = mkCN (mkN "Schlinge");
    Webbing = mkCN (mkN "Schlauchband" "Schlauchbänder" neuter);
    
    Bucket, Jug = mkCN (mkN "Henkel" "Henkel" masculine);
    ChippedHold = mkCN (mkN "geschlagener Griff");
    Crack = mkCN (mkN "Riss");
    Hold = mkCN (mkN "Griff");
    Pocket = mkCN (mkN "Loch" "Löcher" neuter);
    Sloper = mkCN (mkN "Aufleger");
    Undercling = mkCN (mkN "Untergriff");
    
    Bowline = mkCN (mkN "Palstek");
    ButterflyKnot = mkCN (mkN "Schmetterlingsknoten");
    DoubleFisherman = mkCN (mkN "doppelter Spierenstich");
    FigureOfEightKnot = mkCN (mkN "Achtknoten");
    FishermansKnot = mkCN (mkN "Spierenstich");
    Knot = mkCN (mkN "Knoten");
    MunterHitch = mkCN (mkN "Halbmastwurf");
    OverhandBend = mkCN (mkN "Sackstich");
    OverhandKnot = mkCN (mkN "Kreuzschlag");
    PrusikKnot = mkCN (mkN "Prusikknoten");
    ThreadedOverhandKnot = mkCN (mkN "Sackstich in Ringform" "Sackstiche in Ringform" masculine);
    WaterKnot = mkCN (mkN "Bandschlingenknoten");
    
    ProBelayerMale = mkN "Sicherungsmann" "Sicherungsmänner" masculine;
    ProBelayerFemale = mkN "Sicherungsfrau" "Sicherungsfrauen" feminine;
    ProLeaderMale = mkN "Vorsteiger" "Vorsteiger" masculine;
    ProLeaderFemale = mkN "Vorsteigerin" "Vorsteigerinnen" feminine;
    ProTeacherFemale = mkN "Lehrerin" "Lehrerinnen" feminine;
    ProPhysicianFemale = mkN "Ärztin" "Ärztinnen" feminine;
}
