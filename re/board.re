open BsReactNative;

type grid = list(list(bool));

type state = {
  title: string,
  grid
};

type action =
  | Reverse
  | SwitchItem(int, int)
  | BoardMove;

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

let reverseItem = (grid, x, y) =>
  List.mapi(
    (nY, row) =>
      List.mapi((nX, item) => nX === x && nY === y ? ! item : item, row),
    grid
  );

let reducer = (action, state) =>
  switch action {
  | Reverse =>
    ReasonReact.Update({title: reverseString(state.title), grid: state.grid})
  | SwitchItem(x, y) =>
    ReasonReact.Update({
      title: state.title,
      grid: reverseItem(state.grid, x, y)
    })
  | BoardMove =>
    ReasonReact.Update({title: state.title, grid: Life.boardMove(state.grid)})
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
      <Text style=styles##text onPress=(self.reduce(() => BoardMove))>
        (ReasonReact.stringToElement(self.state.title))
      </Text>
      <Grid grid=self.state.grid changeItem=(changeSingleItem(self.reduce)) />
    </View>
};