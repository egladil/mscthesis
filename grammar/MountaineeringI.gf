incomplete concrete MountaineeringI of Mountaineering = Phrasebook ** 
    open
      Syntax,
      Lexicon,
      Symbolic,  -- for names as strings
      Prelude
    in {
  lincat
    Hold = CN;

-- Sentences
  lin
    ADoVerbPhraseDirection p vp x = mkCl p.name (mkVP vp x.to) ;
    AModVerbPhraseDirection m p vp x = mkCl p.name (mkVP m (mkVP vp x.to)) ;
}
