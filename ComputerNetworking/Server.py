#coding=utf-8
import socket, threading, time

linksArray = ['http://www.ynet.co.il/articles/0,7340,L-4713571,00.html',
              'http://www.ynet.co.il/articles/0,7340,L-5045541,00.html',
              'https://www.calcalist.co.il/world/articles/0,7340,L-3726321,00.html',
              'http://www.nrg.co.il/online/13/ART2/902/962.html',
              'http://www.nrg.co.il/online/55/ART2/904/542.html',
              'https://food.walla.co.il/item/3113079',
              'https://news.walla.co.il/item/3114145',
              'https://news.walla.co.il/item/3114283']
imagesArray = ['https://images1.ynet.co.il/PicServer4/2014/08/05/5506384/52203970100690640360no.jpg',
              'https://images1.ynet.co.il/PicServer5/2017/11/23/8172884/817287001000100980704no.jpg',
              'https://images1.calcalist.co.il/PicServer3/2017/11/30/775736/2_l.jpg',
              'http://www.nrg.co.il/images/archive/465x349/1/646/416.jpg',
              'http://www.nrg.co.il/images/archive/465x349/1/795/429.jpg',
              'https://img.wcdn.co.il/f_auto,w_700/2/5/1/3/2513314-46.jpg',
              'https://img.wcdn.co.il/f_auto,w_700/2/4/9/5/2495334-46.jpg',
              'https://img.wcdn.co.il/f_auto,w_700/2/5/1/4/2514588-46.jpg']
headersArray = ['החוש הדומיננטי שיעזור לכם בלימודים',
              '"כ"ט בנובמבר: "שמחה שנמשכה ימים ולילות, הייתה אופוריה"',
              'רוצים נייר טואלט? הזדהו: כך משפרים הסינים את מצב השירותים הציבוריים',
              'מחקו לכם הודעה בווטסאפ? עדיין תוכלו לקרוא אותה',
              'גם בחורף :זה בדיוק הזמן לקפוץ לאילת',
              '12 בתי קפה שמתאימים לעבודה עם לפטופ',
              'שותק על אזריה, נלחם באהוד ברק: בנט מנסה להיבנות כימין ממלכתי',
              'רצח בכל שלושה ימים: צרפת יוצאת למאבק באלימות נגד נשים']
contentsArray = ['החוש הדומיננטי שיעזור לכם בלימודים. אילו טיפים של שימוש בחושים יעזרו לכם?',
              'ב 1947- הם היו ילדים או צעירים בתחילת דרכם, אבל את היום הגורלי ב 29-בנובמבר הם לא שוכחים עד היום. "כולם היו צמודים לרדיו. אני זוכרת את התפרצות השמחה, ריקודים והתחבקויות".',
              'שבוע קרא נשיא סין שי ג‘ינפינג להמשיך את מהפכת השירותים הציבוריים עליה הכריז ב 2015-. עד כה שופצו ונבנו 68 אלף מתקנים',
              'אפליקציה בשם  Notification Historyמאפשרת למשתמשי אנדרואיד לקרוא את הנתונים הזמניים הנשמרים ביומן הפעילות של הסמארטפון, כולל הודעות מחוקות.',
              'העיר הדרומית נעימה לנופש גם בחודשי החורף. כעת מוצעים מחירים אטרקטיביים במיוחד בחבילות שכוללות מגוון אטרקציות, לינה וטיסות',
              'בין אם אתם סטודנטים או עצמאיים, זה תמיד סיפור למצוא בית קפה נעים וטעים לרבוץ בו. קיבצנו עבורכם 12 מקומות אהובים בדיוק למטרה זו, בארבע הערים הגדולות',
              'כשרגב נלחמת ברעש בתאטרון יפו, בנט משנה בשקט את נהלי סל התרבות כך שהחומרים "השמאלנים" ייפלטו. כשהקשת הפוליטית מתרעמת על דיווחי ה"דיל" של טראמפ עם הפלסטינים, בנט שותק עד שהרשות תסרב.',
              'אחרי ש 126- נשים נרצחו בידי בני זוגן בשנה שעברה, הציג מקרון צעדים חדשים למלחמה בתופעה. "זאת בושה לצרפת", אמר הנשיא שאחת מהבטחות הבחירות שלו הייתה להשיג שוויון מגדרי.']


def resourceChanger(link, imageSource, title, contentString):
    content = '<div class="row">\r\n\
                <div class="features">\r\n\
                    <div class="col-md-4 col-sm-6 wow fadeInDown" data-wow-duration="1000ms" data-wow-delay="600ms">\r\n\
                        <div class="feature-wrap">\r\n\
                            <img src="' + imageSource + '" />\r\n\
                            <h2><a href="' + link + '">' + title + '</a></h2>\r\n\
                            <h3>' + contentString + '</h3>\r\n\
                        </div>\r\n\
                    </div><!--/.col-md-4-->\r\n\
                </div><!--/.services-->\r\n\
            </div><!--/.row-->\r\n'
    return content


def getCurrentTime ():
    return time.asctime(time.localtime(time.time()))


def get200Header(contentType):
    headerString = "HTTP/1.1 200 OK\r\n\
Date:" + getCurrentTime() + " GMT\r\n\
Server: www.my-news-website.co.il (Win32)\r\n\
Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT\r\n\
Content-Type: " + contentType + "\r\n\
Connection: Closed\r\n\
\r\n"
    return headerString


def get404Header(contentType):
    headerString = "HTTP/1.1 404 Not Found\r\n\
Date:" + getCurrentTime() + " GMT\r\n\
Server: www.my-news-website.co.il (Win32)\r\n\
Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT\r\n\
Content-Type: " + contentType + "\r\n\
Connection: Closed\r\n\
\r\n"
    return headerString


def buildStaticContent(path):
    if(not path.startswith('Files')):
        path = 'Files/' + path
    try:
        f = open(path,"rb")
        content = f.read()
        return content
    except IOError:
        return 'IOError'


def buildDynamicContent(numOfArticles):
    try:
        f = open('Files/template.html',"rb")
        fileContent = f.read()
        templateArray = [fileContent.split('<div class="row">')[0],fileContent.split('</div><!--/.row-->')[1]]
        content = templateArray[0]
        for i in range(numOfArticles):
            content += resourceChanger(linksArray[i],imagesArray[i],headersArray[i],contentsArray[i])
        content += templateArray[1]
        return content
    except IOError:
        return 'IOError'


def buildHeader(path,status):
    if('/images' in path):
        contentType = 'image/'
    else:
        contentType = 'text/'
    extension = path.split('.')
    contentType += extension[len(extension) - 1]
    if (status == 200):
        return get200Header(contentType)
    elif(status == 404):
        return get404Header(contentType)


server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_ip = '127.0.0.1'
server_port = 80
server.bind((server_ip, server_port))
server.listen(5)
while True:
    header = ''
    content = ''
    client_socket, client_address = server.accept()
    print 'Connection from: ', client_address
    data = client_socket.recv(1024)
    if (data == ''):
        continue
    print 'Received: ', data
    request = data.split()[1]
    if ('/homepage' not in request):
        path = request.split('?')[0][1:]
        content = buildStaticContent(path)
        if (content == 'IOError'):
            header = buildHeader(path, 404)
            #response = header
        else:
            header = buildHeader(path, 200)
    else:
        numOfArticles = int(request.split('?')[1].split('=')[1])
        content = buildDynamicContent(numOfArticles)
        header = get200Header('text/html')
    response = header + content
    print 'Sent: ' + header
    client_socket.send(response)
    print 'Client disconnected'
    client_socket.close()