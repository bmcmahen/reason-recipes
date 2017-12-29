let uuid: unit => string = [%bs.raw {|function() {return Math.random().toString(16).slice(2)}|}];

let eventValue: ReactEventRe.Form.t => string =
  (event) => ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value;