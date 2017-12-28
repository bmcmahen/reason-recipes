let fb = DB.fb;

Firebase.enablePersistence(Firebase.firestore(fb))
|> Js.Promise.catch(
     (err) => {
       Js.log2("error", err);
       Js.Promise.resolve()
     }
   )
|> Js.Promise.then_(
     () => {
       ReactDOMRe.renderToElementWithId(<App auth=(Firebase.auth(fb)) fb />, "index");
       Js.Promise.resolve()
     }
   );