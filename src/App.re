let str = ReasonReact.string;

let component = ReasonReact.statelessComponent("App");

module VideoGames = [%graphql
  {|
  query VideoGames {
    videoGames {
      id
      title
      developer
      completed
    }
  }
|}
];

module VideoGamesQuery = ReasonApollo.CreateQuery(VideoGames);

let make = _children => {
  ...component,
  render: _self => {
    let videoGamesQuery = VideoGames.make();
    <div>
      <h1> {"ReasonML + ReasonReact + GraphQL" |> str} </h1>
      <VideoGamesQuery variables=videoGamesQuery##variables>
        ...{
             ({result}) =>
               switch (result) {
               | Loading => <div> {"Loading!" |> str} </div>
               | Error(error) => <div> {error##message |> str} </div>
               | Data(data) => <VideoGameList items=data##videoGames />
               }
           }
      </VideoGamesQuery>
    </div>;
  },
};