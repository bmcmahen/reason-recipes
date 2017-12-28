open Nice;

let buttonStyle =
  css([
    FontWeight(Bold),
    BorderWidth(Px(0)),
    Color(RGBa(67, 90, 111, 0.845)),
    BackgroundImage("linear-gradient(to top, rgba(67,90,111,0.114), rgba(67,90,111,0.041))"),
    Cursor(Pointer),
    Padding(Em(0.75)),
    PaddingRight(Em(2.0)),
    PaddingLeft(Em(2.0)),
    BorderRadius(Em(0.3)),
    FontSize(Em(0.9)),
    FontWeight(W400),
    FontFamily("Helvetica Neue"),
    BoxShadow(
      "rgba(67, 90, 111, 0.145) 0px 0px 0px 1px inset, rgba(67, 90, 111, 0.08) 0px -1px 1px 0px inset"
    )
  ]);

let component = ReasonReact.statelessComponent("Button");

let make = (~onClick, children) => {
  ...component,
  render: (_self) => <button onClick className=buttonStyle> children </button>
};