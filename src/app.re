type user = ReactTemplate.Firebase.Auth.user;

type action =
  | ShowAllRecipes
  | AuthStateChanged(option(user));

type showing =
  | AllRecipes;

type state = {
  showing,
  user: option(user)
};

let component = ReasonReact.reducerComponent("App");

let make = (~auth, ~fb, _children) => {
  ...component,
  reducer: (action, state) =>
    switch action {
    | ShowAllRecipes => ReasonReact.Update({...state, showing: AllRecipes})
    | AuthStateChanged(user) => ReasonReact.Update({...state, user})
    },
  initialState: () => {
    showing: AllRecipes,
    user: Firebase.Auth.currentUser(auth) |> Js.Nullable.to_opt
  },
  didMount: ({reduce}) => {
    let router = DirectorRe.makeRouter({"/": reduce((_) => ShowAllRecipes)});
    DirectorRe.init(router, "/");
    Firebase.Auth.onAuthStateChanged(
      auth,
      reduce((user) => AuthStateChanged(user |> Js.Nullable.to_opt))
    );
    ReasonReact.NoUpdate
  },
  render: (self) =>
    <div>
      <Navbar fb auth user=self.state.user />
      <div> (ReasonReact.stringToElement("hello world")) </div>
    </div>
};