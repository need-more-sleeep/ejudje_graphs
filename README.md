# ejudje_graphs
## Уязвимые зависимости
Реализуйте вывод всех путей до уязвимых библиотек для проекта.
### Формат ввода
Данные передаются через стандартный поток ввода.
Первая строка содержит идентификаторы уязвимых библиотек, разделенные пробелом.
Вторая строка содержит идентификаторы прямых зависимостей проекта, разделенные пробелом.
Каждая последующая строка содержит идентификатор зависимости и идентификаторы библиотек, от которых она зависит, разделенные пробелом.
### Формат вывода
Результат работы программы выводится в стандартный поток вывода.
Каждая строка должна содержать путь (набор идентификаторов, разделенный пробелом) к уязвимой зависимости.
Начало пути — прямая зависимость проекта, конец — уязвимая библиотека.
Порядок строк не имеет значения.
### Пример
#### Ввод:
log4j iseven hacked browserslist kgb-bot glob-parent css-what iotjs undertow wordpress cancer ant go rUst
jupiter sl4j somelib pwned site hacked hAcKeD security
sl4j console time log4j
jupiter junit
nothing void
site developer time coffee
kgb-bot libpoe-component-irc-perl libpoe-component-server-soap-perl libpoe-perl libproc-pid-file-perl libschedule-ratelimiter-perl libyaml-perl lsb-base perl
developer food water sleep chocolate friends wordpress love time english fizraToBeStrong computer stickers
junit java ant
somelib nothing
light void
darkness void
spanishInquisition nobody
void everything
everything sl4j console jupiter junit site developer time coffee kgb-bot food water sleep chocolate friends wordpress love time english fizraToBeStrong computer stickers java ant
#### Вывод:
hacked
sl4j log4j
jupiter junit ant
site developer wordpress
somelib nothing void everything sl4j log4j
somelib nothing void everything jupiter junit ant
somelib nothing void everything junit ant
somelib nothing void everything ant
somelib nothing void everything site developer wordpress
somelib nothing void everything developer wordpress
somelib nothing void everything wordpress
somelib nothing void everything kgb-bo
