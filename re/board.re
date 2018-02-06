open BsReactNative;

type state = {
  title: string,
  grid: list(list(bool))
};

type action =
  | Reverse
  | SwitchItem(int, int)
  | ChangeOne;

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
  | ChangeOne =>
    ReasonReact.Update({
      title: state.title,
      grid: reverseItem(state.grid, 1, 1)
    })
  };

/*let changeItem = (reduce, x, y) => reduce((_) => SwitchItem(x, y));*/
/* ReasonReact.Update({grid: reverseItem(grid, x, y)}) */
/*let handleCanvas = canvas => Js.log(canvas);*/
let make = _children => {
  ...component,
  initialState,
  reducer,
  render: ({state, reduce}) =>
    <View style=styles##wrapper>
      <Text style=styles##text onPress=(reduce(() => Reverse))>
        (ReasonReact.stringToElement(state.title))
      </Text>
      <Grid grid=state.grid changeItem=(reduce(() => ChangeOne)) />
    </View>
};