type state =
  | Saving
  | Editing;

let component = ReasonReact.reducerComponent("Compose");

let make = (~fb, ~uid, _children) => {
  ...component,
  initialState: () => Editing,
  reducer: (action, _) => ReasonReact.Update(action),
  render: ({state, reduce}) => {
    let id = BaseUtils.uuid();
    <EditRecipe
      saving=(state === Saving)
      recipe=(Models.Recipe.blank(id, uid))
      onSave=(
        (recipe) => {
          reduce((_) => Saving);
          module FB = Firebase.Collection(Models.Recipe);
          let collection = FB.get(fb);
          let doc = Firebase.doc(collection, recipe##id);
          Js.log2("Saving", recipe);
          Firebase.set(doc, recipe)
          |> Js.Promise.then_(() => Js.Promise.resolve())
          |> Js.Promise.catch(
               (err) => {
                 Js.log(err);
                 Js.Promise.resolve()
               }
             )
          |> ignore
        }
      )
    />
  }
};