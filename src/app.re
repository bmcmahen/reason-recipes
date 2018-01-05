type user = ReactTemplate.Firebase.Auth.user;

type routes =
  | AllRecipes
  | NewRecipe;

module LoggedIn = {
  let component = ReasonReact.statelessComponent("LoggedIn");
  let make = (~auth, ~user, ~router, ~route, ~fb, _children) => {
    ...component,
    render: (_self) =>
      switch route {
      | AllRecipes => <div> (ReasonReact.stringToElement("all recipes")) </div>
      | NewRecipe => <div> (ReasonReact.stringToElement(" new recipe")) </div>
      }
  };
};

module InitRouter = {
  let component = ReasonReact.statelessComponent("InitRouter");
  let make = (~router=?, children) => {
    ...component,
    render: (_self) =>
      switch router {
      | Some(_router) => children
      | None => ReasonReact.nullElement
      }
  };
};

type action =
  | ShowAllRecipes
  | AddNewRecipe
  | AuthStateChanged(option(user));

type state = {
  showing: routes,
  user: option(user),
  router: option(DirectorRe.t)
};

let component = ReasonReact.reducerComponent("App");

let make = (~auth, ~fb, _children) => {
  ...component,
  reducer: (action, state) =>
    switch action {
    | ShowAllRecipes => ReasonReact.Update({...state, showing: AllRecipes})
    | AddNewRecipe => ReasonReact.Update({...state, showing: NewRecipe})
    | AuthStateChanged(user) => ReasonReact.Update({...state, user})
    },
  initialState: () => {
    showing: AllRecipes,
    user: Firebase.Auth.currentUser(auth) |> Js.Nullable.to_opt,
    router: None
  },
  didMount: ({reduce, state}) => {
    let router =
      DirectorRe.makeRouter({
        "/": reduce((_) => ShowAllRecipes),
        "/compose": reduce((_) => AddNewRecipe)
      });
    DirectorRe.init(router, "/");
    Firebase.Auth.onAuthStateChanged(
      auth,
      reduce((user) => AuthStateChanged(user |> Js.Nullable.to_opt))
    );
    ReasonReact.Update({...state, router: Some(router)})
  },
  render: (self) =>
    switch (self.state.router, self.state.user) {
    | (Some(router), Some(user)) =>
      <div>
        <Navbar router fb auth user=self.state.user />
        <LoggedIn router user fb auth route=self.state.showing />
      </div>
    | (Some(router), _) => <div> <Navbar router fb auth user=self.state.user /> </div>
    | _ => <div> (ReasonReact.stringToElement("initializing router")) </div>
    }
};