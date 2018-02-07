open BsReactNative;

type grid = list(list(bool));

type state = grid;

type action =
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

let makeAGrid = (size: int) => {};

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

let initialState = () => grid;

let reverseItem = (grid, x, y) =>
  List.mapi(
    (nY, row) =>
      List.mapi((nX, item) => nX === x && nY === y ? ! item : item, row),
    grid
  );

let reducer = (action, state) =>
  switch action {
  | SwitchItem(x, y) => ReasonReact.Update(reverseItem(state, x, y))
  | BoardMove => ReasonReact.Update(Life.boardMove(state))
  };

let changeSingleItem = (reduce, x, y) => reduce(() => SwitchItem(x, y));

let make = _children => {
  ...component,
  subscriptions: self => [
    Sub(
      () => Js.Global.setInterval(self.reduce(() => BoardMove), 1000),
      Js.Global.clearInterval
    )
  ],
  initialState,
  reducer,
  render: self =>
    <View style=styles##wrapper>
      <Text style=styles##text onPress=(self.reduce(() => BoardMove))>
        (ReasonReact.stringToElement("Next move"))
      </Text>
      <Grid grid=self.state changeItem=(changeSingleItem(self.reduce)) />
    </View>
};