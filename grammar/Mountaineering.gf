abstract Mountaineering = Phrasebook ** {
  cat
    HoldKind;  -- Anything and everything that can be used as a hold when climbing.
    KnotKind;  -- Knots.
    Profession;
    
  fun
  	HoldToPlaceKind : HoldKind -> PlaceKind;	-- Maybe it isn't a place after all since the prepositions are weird (see concrete)
  	KnotToKind : KnotKind -> Kind;
  	
    ThisProfession, ThatProfession : Profession -> Person;      -- this teacher, that teacher
    TheseProfessions, ThoseProfessions : Profession -> Person;  -- these teachers,those teachers
    TheProfession, TheProfessions : Profession -> Person;       -- the teacher, the teachers

-- Sentences
  fun
    ADoVerbPhraseDirection  : Person -> VerbPhrase -> Place -> Action ;              -- I walk to the hotel
    AModVerbPhraseDirection : Modality -> Person -> VerbPhrase -> Place -> Action ;  -- I can walk to the hotel
    
    IsAProfession : Person -> Profession -> Action;
  
-- Words
  fun
    BelayStation : PlaceKind;
    Cliff : PlaceKind;
    ClimbingGym : PlaceKind;
    Glacier : PlaceKind;
    Mountain : PlaceKind;
    Overhang : PlaceKind;
    Summit : PlaceKind;
    
    VAbseil, VRappel : VerbPhrase;
    VBelay : VerbPhrase;
    VBoulder : VerbPhrase;
    VClimb : VerbPhrase;
    VFall : VerbPhrase;
    VLead : VerbPhrase;
    VStem : VerbPhrase;
    
    V2Tie : Object -> VerbPhrase;
    
    GBelayOn : Greeting;
    GBelow, GRock : Greeting;
    GClimbing : Greeting;
    GFalling : Greeting;
    GOffBelay, GSafe : Greeting;
    GRope : Greeting;
    GSlack : Greeting;
    GUpRope : Greeting;
    
    Ascender : Kind;
    Bolt : Kind;
    Carabiner : Kind;
    Chalk : MassKind;
    ChestHarness : Kind;
    ClimbingShoe : Kind;
    Cord : Kind;
    Crampon : Kind;
    ExpansionBolt : Kind;
    HalfRope : Kind;
    Harness : Kind;
    Helmet : Kind;
    IceAxe : Kind;
    Jumar : Kind;
    LockingCarabiner : Kind;
    Nut : Kind;
    Piton : Kind;
    Rack : MassKind;
    Ring : Kind;
    Rope : Kind;
    Runner, Sling : Kind;
    Webbing : Kind;
    
    Bucket, Jug : HoldKind;
    Chickenhead : HoldKind;
    ChippedHold : HoldKind;
    Crack : HoldKind;
    Hold : HoldKind;
    Pocket : HoldKind;
    Sidepull : HoldKind;
    Sloper : HoldKind;
    Undercling : HoldKind;
    
    Bowline : KnotKind;
    ButterflyKnot : KnotKind;
    DoubleFisherman : KnotKind;
    FigureOfEightKnot : KnotKind;
    FishermansKnot : KnotKind;
    Knot : KnotKind;
    MunterHitch : KnotKind;
    OverhandBend : KnotKind;
    OverhandKnot : KnotKind;
    PrusikKnot : KnotKind;
    ThreadedOverhandKnot : KnotKind;
    WaterKnot : KnotKind;
    
    ProBelayerMale, ProBelayerFemale : Profession;
    ProClimberMale, ProClimberFemale : Profession;
    ProLeaderMale, ProLeaderFemale : Profession;
    ProSecondMale, ProSecondFemale : Profession;
    ProTeacherMale, ProTeacherFemale : Profession;
    ProPhysicianMale, ProPhysicianFemale : Profession;
}
