open BsReactNative;

type state = {
  title: string,
  grid: list(list(bool))
};

type action =
  | Reverse
  | SwitchItem(int, int);

let component = ReasonReact.reducerComponent("Board");

let styles =
  StyleSheet.create(
    Style.(
      {
        "wrapper":
          style([width(Pct(100.0)), padding(Pt(10.0)), marginTop(Pt(-10.0))]),
        "text": style([fontSize(Float(16.0)), color("red"), padding(Pt(10.0))])
      }
    )
  );

let reverseString = str => str ++ "!";

let grid = [
  [false, true, false, true],
  [true, false, true, false],
  [false, true, false, true],
  [true, false, true, false]
];

let initialState = () => {title: "horses", grid};

let reverseItem = (grid, x, y) => grid;

let reducer = (action, state) =>
  switch action {
  | Reverse =>
    ReasonReact.Update({title: reverseString(state.title), grid: state.grid})
  | SwitchItem(x, y) =>
    ReasonReact.Update({title: state.title, grid: reverseItem(grid, x, y)})
  };

let changeItem = (x, y) => SwitchItem(x, y);

/* ReasonReact.Update({grid: reverseItem(grid, x, y)}) */
/*let handleCanvas = canvas => Js.log(canvas);*/
let make = _children => {
  ...component,
  initialState,
  reducer,
  render: self =>
    <View style=styles##wrapper>
      <Text style=styles##text onPress=(self.reduce(() => Reverse))>
        (ReasonReact.stringToElement(self.state.title))
      </Text>
      <Grid grid=self.state.grid changeItem=(self.reduce(changeItem)) />
    </View>
};