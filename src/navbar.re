open Nice;

open Util;

let className = css([Display(Flex), Color(Red)]);

let component = ReasonReact.statelessComponent("Navbar");

let make = (~user, ~auth, ~router, ~fb, _children) => {
  /** Password login */
  let onClick = (_event) =>
    Firebase.Auth.signInWithEmailAndPassword(auth, "ben.mcmahen@gmail.com", "awesomepassword")
    |> Js.Promise.then_(
         (user) => {
           Js.log(user);
           Js.Promise.resolve()
         }
       )
    |> Js.Promise.catch(
         (err) => {
           Js.log(err);
           Js.Promise.resolve()
         }
       )
    |> ignore;
  let compose = (_event) => DirectorRe.setRoute(router, "/compose");
  let signOut = (_event) => Firebase.Auth.signOut(auth) |> ignore;
  /** Google login with Firebase */
  let loginWithGoogle = (_event) => {
    let getProvider: unit => Firebase.Auth.provider = [%bs.raw
      {|
      function () {
        const firebase = require('firebase');
        return new firebase.auth.GoogleAuthProvider();
      }
    |}
    ];
    Firebase.Auth.signInWithPopup(auth, getProvider())
    |> Js.Promise.then_(
         (loginResult) => {
           Js.log(loginResult);
           Js.Promise.resolve()
         }
       )
    |> Js.Promise.catch(
         (err) => {
           Js.log(err);
           Js.Promise.resolve()
         }
       )
    |> ignore
  };
  {
    ...component,
    didMount: (_self) => {
      Js.log(auth);
      ReasonReact.NoUpdate
    },
    render: (_self) =>
      <div className="Navbar">
        (
          switch user {
          | Some(_session) =>
            <div>
              <Button onClick=signOut> ...(str("Sign out")) </Button>
              <Button onClick=compose> ...(str("Compose")) </Button>
            </div>
          | None =>
            <div>
              <Button onClick=loginWithGoogle>
                ...("Login with Google" |> ReasonReact.stringToElement)
              </Button>
              <button onClick> (ReasonReact.stringToElement("Login with email")) </button>
            </div>
          }
        )
      </div>
  }
};