abstract Mountaineering = Phrasebook ** {
  cat
    Hold;  -- Anything and everything that can be used as a hold when climbing.
    
  fun
  	HoldPlaceKind : Hold -> PlaceKind;	-- Maybe it isn't a place after all since the prepositions are weird (see concrete)

-- Sentences
  fun
    ADoVerbPhraseDirection  : Person -> VerbPhrase -> Place -> Action ;              -- I walk to the hotel
    AModVerbPhraseDirection : Modality -> Person -> VerbPhrase -> Place -> Action ;  -- I can walk to the hotel
  
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
    
    Bucket, Jug : Hold;
    Chickenhead : Hold;
    ChippedHold : Hold;
    Crack : Hold;
    NHold : Hold;
    Pocket : Hold;
    Sidepull : Hold;
    Sloper : Hold;
    Undercling : Hold;
}
