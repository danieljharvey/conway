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
  [false, false, false, false, false, false, false],
  [false, false, false, false, false, false, false],
  [false, false, false, false, false, false, false],
  [false, false, false, false, false, false, false],
  [false, false, false, false, false, false, false],
  [false, false, false, false, false, false, false],
  [false, false, false, false, false, false, false],
  [false, false, false, false, false, false, false]
];

let initialState = () => {title: "horses", grid};

let reverseRow = (x, y, nY, row) =>
  Array.to_list(
    Array.mapi(
      (nX, item) => nX === x && nY === y ? ! item : item,
      Array.of_list(row)
    )
  );

let reverseItem = (grid, x, y) =>
  Array.to_list(Array.mapi(reverseRow(x, y), Array.of_list(grid)));

let reducer = (action, state) =>
  switch action {
  | Reverse =>
    ReasonReact.Update({title: reverseString(state.title), grid: state.grid})
  | SwitchItem(x, y) =>
    ReasonReact.Update({
      title: state.title,
      grid: reverseItem(state.grid, x, y)
    })
  };

let changeSingleItem = (reduce, x, y) => reduce(() => SwitchItem(x, y));

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
      <Grid grid=self.state.grid changeItem=(changeSingleItem(self.reduce)) />
    </View>
};