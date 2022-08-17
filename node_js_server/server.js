const express = require('express');
const bodyParser = require('body-parser');
// const http = require('http');
const path = require('path');
const helmet = require('helmet');
const rateLimit = require('express-rate-limit');

const handlebarsEngine = require('express-handlebars');

const app = express();

app.set('views', path.join(__dirname, './public'));
app.set('view engine', 'handlebars');
app.engine('handlebars', handlebarsEngine.engine());

app.use(bodyParser.urlencoded({ extended: true }));
app.use(express.static(path.join(__dirname, './public')));
app.use(helmet());
app.use(rateLimit({
  windowMs: 5 * 60 * 1000,
  max: 100
}));

app.use(function(req, res, next) {
  res.setHeader(
    'Content-Security-Policy',
    "script-src https://ajax.googleapis.com https://cdn.jsdelivr.net 'unsafe-inline'"
  );
  next();
});

app.get('/', function(req, res) {
  res.render('trig');
});
app.get('/trig', function(req, res) {
  //res.render('trig', { response: req.body });
  res.json(req.body)
});

app.listen(8080);