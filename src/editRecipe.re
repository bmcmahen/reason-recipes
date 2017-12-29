open BaseUtils;

module Styles = {
  open Nice;
  let title = css([Nice.FontWeight(Nice.Bold)]);
};

let str = ReasonReact.stringToElement;

type state = {
  title: string,
  description: string,
  content: string
};

type action =
  | SetTitle(string)
  | SetDescription(string)
  | SetContent(string);

let component = ReasonReact.reducerComponent("EditRecipe");

let make = (~saving, ~recipe, ~onSave, _children) => {
  ...component,
  initialState: () => {title: "", description: "", content: ""},
  reducer: (action, state) =>
    switch action {
    | SetTitle(title) => ReasonReact.Update({...state, title})
    | SetDescription(description) => ReasonReact.Update({...state, description})
    | SetContent(content) => ReasonReact.Update({...state, content})
    },
  render: ({state, reduce}) =>
    <div>
      <h1 className=Styles.title> (str("add recipe")) </h1>
      <label> (str("Title")) </label>
      <input id="title" value=state.title onChange=(reduce((evt) => SetTitle(eventValue(evt)))) />
    </div>
};