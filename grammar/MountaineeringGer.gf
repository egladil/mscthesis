--# -path=.:present:alltenses

concrete MountaineeringGer of Mountaineering = PhrasebookGer ** 
    MountaineeringI with 
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
    HoldPlaceKind x = mkCNPlace x (mkPrep "bei" dative) zu_Prep;

-- Words
  lin
    BelayStation = mkPlace (mkN "Standplatz" "Standpl�tze" masculine) on_Prep zu_Prep;
    Cliff = mkPlace (mkN "Fels" "Felsen" masculine) on_Prep zu_Prep;
    ClimbingGym = mkPlace (mkN "Kletterhalle" "Kletterhallen" feminine) in_Prep inAcc_Prep;
    Glacier = mkPlace (mkN "Gletscher") on_Prep zu_Prep;
    Mountain = mkPlace (L.mountain_N) on_Prep zu_Prep;
    Overhang = mkPlace (mkN "�berhang" "�berh�nge" masculine) in_Prep inAcc_Prep;
    Summit = mkPlace (mkN "Gipfel") on_Prep zu_Prep;
    
    VAbseil, VRappel = mkVP (regV "abseilen");
    VBelay = mkVP (regV "sichern");
    VBoulder = mkVP (regV "bouldern");
    VClimb = mkVP (regV "klettern");
    VFall = mkVP (regV "st�rzen");
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
    Cord = mkCN (mkN "Reepschnur" "Reepschn�re" feminine);
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
    Webbing = mkCN (mkN "Schlauchband" "Schlauchb�nder" neuter);
    
    Bucket, Jug = mkCN (mkN "Henkel" "Henkel" masculine);
    ChippedHold = mkCN (mkN "geschlagener Griff");
    Crack = mkCN (mkN "Riss");
    NHold = mkCN (mkN "Griff");
    Pocket = mkCN (mkN "Loch" "L�cher" neuter);
    Sloper = mkCN (mkN "Aufleger");
    Undercling = mkCN (mkN "Untergriff");
}
