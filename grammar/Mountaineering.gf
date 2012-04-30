abstract Mountaineering = Phrasebook ** {
  fun
    BelayStation : PlaceKind;
    Cliff : PlaceKind;
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
    GFalling : Greeting;
    GOffBelay, GSafe : Greeting;
    GRope : Greeting;
    GSlack : Greeting;
    GUpRope : Greeting;
}
