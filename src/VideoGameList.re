open VideoGame;

let str = ReasonReact.string;
let component = ReasonReact.statelessComponent("VideoGameList");

module CompleteGame = [%graphql
  {|
  mutation CompleteGame($id: ID!) {
    completeGame(id: $id) {
      id
      completed
    }
  }
|}
];

module CompleteGameMutation = ReasonApollo.CreateMutation(CompleteGame);

let make = (~items, _children) => {
  ...component,
  render: _self =>
    <ul style={ReactDOMRe.Style.make(~listStyleType="none", ())}>
      {
        items
        |> Array.map(videoGameFromJs)
        |> Array.map(item =>
             <li key={item.id}>
               <CompleteGameMutation>
                 ...{
                      (mutate, {result}) => {
                        let loading = result == Loading;
                        <div>
                          <input
                            id={item.id}
                            type_="checkbox"
                            checked={item.completed}
                            onChange={
                              _event => {
                                let completeGame =
                                  CompleteGame.make(~id=item.id, ());
                                mutate(~variables=completeGame##variables, ())
                                |> ignore;
                              }
                            }
                          />
                          <label
                            htmlFor={item.id}
                            style={
                              ReactDOMRe.Style.make(
                                ~color=loading ? "orange" : "default",
                                (),
                              )
                            }>
                            {item.title ++ " | " ++ item.developer |> str}
                          </label>
                        </div>;
                      }
                    }
               </CompleteGameMutation>
             </li>
           )
        |> ReasonReact.array
      }
    </ul>,
};