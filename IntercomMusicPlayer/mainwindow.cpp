#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Bev Facey Intercom Music Player");
    widget = new QWidget;
    layout = new QVBoxLayout(widget);
    widget1 = new QWidget;
    layout1 = new QVBoxLayout(widget1);
    ui->Pause_Button->setDisabled(true); //Disabling Pause Button
    ui->Stop_Button->setDisabled(true); //Disabling Stop Button
    ui->Time_Slider->setDisabled(true); //Disabling Slider
    timer = new QTimer; //Setting up status label
    connect(timer, SIGNAL(timeout()), this, SLOT(setStatus()));
    timer->start(10);
    device = 1; //Setting device as 1 = Default speaker
    BASS_SetVolume(0.5); //Setting Volume to 50%
    ui->VU_Meter->setDisabled(true); //Setting VU meters all disable and invisible
    ui->VU_Meter_2->setDisabled(true);
    ui->VU_Meter->setVisible(false);
    ui->VU_Meter_2->setVisible(false);
    ui->Speed_Slider->setVisible(false);
    ui->debugEnable_checkBox->setVisible(false);
    ui->debug_timeEdit->setVisible(false);

    QBrush tb(Qt::transparent); // Transparent brush, solid pattern
    ui->Secret_Button->setFlat(true);
    ui->Secret_Button->setPalette(QPalette(tb, tb, tb, tb, tb, tb, tb, tb, tb));

    on_actionPlaylist_Mode_triggered();

    //ids = new ID3v1_1();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ISound_Button_clicked() //Insert_Sound Button
{
    QFileDialog getfile;
    getfile.setFileMode(QFileDialog::ExistingFiles);
    getfile.setNameFilter(tr("Audio files (*.mp3 *.wav *.ogg *.aiff);; All Files (*.*)"));
    if(getfile.exec() == QFileDialog::Accepted) //Executing File Dialog
    {
    QStringList directory = getfile.selectedFiles();
    if(directory.size() >= 2)
    {
        for(int a = 0; a < directory.count(); a++)
        {
            QFileInfo filename(directory.at(a));
            QPushButton *button = new QPushButton(filename.fileName());
            button->setToolTip(directory.at(a));
            layout->addWidget(button);
            buttons.append(button);
            connect(button, SIGNAL(clicked(bool)), this, SLOT(on_Button_Clicked()));
        }
        ui->random_Button->setEnabled(true);
    }else{
        QFileInfo filename(directory.at(0));
        QPushButton *button = new QPushButton(filename.fileName());
        button->setToolTip(directory.at(0));
        layout->addWidget(button);
        buttons.append(button);
        connect(button, SIGNAL(clicked(bool)), this, SLOT(on_Button_Clicked()));
    }    
    ui->scrollArea->setWidget(widget);
    }
}

void MainWindow::on_Button_Clicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender()); //Getting the button that has been pressed

    if(button == NULL)
    {
        return;
    }

    if(ifremove) //Checking if remove button is active
    {
        if(button == current)
        {
            BASS_ChannelStop(stream);
            BASS_ChannelStop(stream1);
            BASS_ChannelStop(stream2);
        }
        buttons.removeOne(button);
        delete button;
    }else if(ifedit)
    {
        editcurrent = button;
        ui->Status_Label->setText("Selected Button: " + button->text());
        ui->Next_Button->setEnabled(true);
        ui->Previous_Button->setEnabled(true);
    }else{
        if(ifplaylist)
        {
        /*if(current_song_number != -1 && ifplaylist == true) //Crash
        {
            if(button != current && button != NULL && button->objectName() != "Next_Button" && button->objectName() != "Previous_Button")
            {
            current_song_number = -1;
            }
        }*/
        if(current_song_number > 0 && button != NULL && button->objectName() == "Previous_Button")
        {
            current_song_number--;
            button = buttons.at(current_song_number);
        }else if(current_song_number < buttons.size() - 1 && button != NULL && button->objectName() == "Next_Button")
        {
            current_song_number++;
            button = buttons.at(current_song_number);
        }else{
            current_song_number = buttons.indexOf(button);
        }
        }else{
            current_song_number = buttons.indexOf(button);
        }
        current = button;
        playSound(button->toolTip());
        ui->Next_Button->setEnabled(true);
        ui->Previous_Button->setEnabled(true);
    }
}

void MainWindow::playList()
{
    ui->Next_Button->setEnabled(true);
    ui->Previous_Button->setEnabled(true);
    /*if(current_song_number != -1 && ifplaylist == true) //Crash
    {
        if(button != current && button != NULL && button->objectName() != "Next_Button" && button->objectName() != "Previous_Button")
        {
        current_song_number = -1;
        }
    }*/
    //if(current_song_number == -1) //Not getting -1 when it is clicked
    //{
    //current_song_number = buttons.indexOf(button);
    //}else if(current_song_number < buttons.size() - 1)
    //{
    //}
    if(ifplaylist == true)
    {
        if(current_song_number + 1 < buttons.size())
        {
        current_song_number++;
        current = buttons.at(current_song_number);
        playSound(buttons.at(current_song_number)->toolTip());
        }else{
            current_song_number = 0;
            current = buttons.at(current_song_number);
            playSound(buttons.at(current_song_number)->toolTip());
        }
    }
}

void MainWindow::playSound(QString string)
{
    if(ifpress)
    {}else{
    BASS_ChannelStop(stream); //Stopping the last played music
    BASS_ChannelStop(stream1); //Stopping the last played music
    BASS_ChannelStop(stream2); //Stopping the last played music
    }

    BASS_Init(device, Samplerate, 0, 0, NULL); //Initiazing BASS audio player

    BASS_Init(device1, Samplerate, 0 ,0, NULL); //Initiazing BASS 2 audio player

    BASS_Init(device2, Samplerate, 0 ,0, NULL); //Initiazing BASS 3 audio player

    BASS_SetDevice(device);

    stream = BASS_StreamCreateFile(FALSE, string.toLatin1().constData(), 0, 0, BASS_STREAM_AUTOFREE); //Creating new audio stream

    BASS_SetDevice(device1);

    stream1 = BASS_StreamCreateFile(FALSE, string.toLatin1().constData(), 0, 0, BASS_STREAM_AUTOFREE); //Creating new audio stream

    BASS_SetDevice(device2);

    stream2 = BASS_StreamCreateFile(FALSE, string.toLatin1().constData(), 0, 0, BASS_STREAM_AUTOFREE); //Creating new audio stream

    if(stream)
    {
        //player.setMedia(QUrl::fromLocalFile(string));
        BASS_ChannelSetSync(stream, BASS_SYNC_END, 0, &MainWindow::EndSyncProc, this); //Syncing
        BASS_ChannelPlay(stream, 0); //Playing the audio
        BASS_ChannelPlay(stream1, 0);
        BASS_ChannelPlay(stream2, 0);
        StreamState = BASS_ChannelIsActive(stream); //Setting BASS to be active
        BASS_SetDevice(device);
        BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, volume);
        BASS_SetDevice(device1);
        BASS_ChannelSetAttribute(stream1, BASS_ATTRIB_VOL, volume);
        BASS_SetDevice(device2);
        BASS_ChannelSetAttribute(stream2, BASS_ATTRIB_VOL, volume);
        ui->Time_Slider->setMaximum(BASS_ChannelBytes2Seconds(stream, BASS_ChannelGetLength(stream, BASS_POS_BYTE)) * 10000); //Setting the slider value to the length of the audio
    }else{
        int ErrorCode = BASS_ErrorGetCode();
        if(ErrorCode != 2)
        {
        QMessageBox::warning(this, "Error", "ErrorCode: " + QString::number(ErrorCode) + " - BASS_ERROR_HANDLE\nPlease check if the format of the selected file is supported.\nIf you are constantly having this issue, please contact the developer!");
        return;
        }
        playList();
        return;
    }

    ui->Pause_Button->setEnabled(true);
    ui->Stop_Button->setEnabled(true);
    ui->Time_Slider->setEnabled(true);
}

void MainWindow::EndSyncProc(HSYNC handle, DWORD channel, DWORD data, void *user)
{
    MainWindow* pMainWindow = reinterpret_cast<MainWindow *>(user);
}

void MainWindow::listChanged()
{
    layout->addWidget(new QPushButton(""));

    ui->scrollArea->setWidget(widget);
}

void MainWindow::on_Setting_Button_clicked() //Setting_Button
{
    Settings settings; // Setting the setting in the setting dialog
    settings.setDevice(device);
    settings.setDevice1(device1);
    settings.setDevice2(device2);
    settings.setVolume(volume * 100);
    settings.setPress(ifpress);
    settings.setPlaylist(ifplaylist);
    settings.setSampleRate(Samplerate);
    settings.setRandom(ifRandom);
    settings.setFade(fade * 100000);
    settings.setNoDial(ifNoDial);

    settings.exec(); //Executing

    OutputDevice = settings.getDevice(); //Getting the chosen devices
    OutputDevice1 = settings.getDevice1();
    OutputDevice2 = settings.getDevice2();

    device = OutputDevice.toInt(); //Getting device id
    device1 = OutputDevice1.toInt();
    device2 = OutputDevice2.toInt();
    volume = settings.getVolume() * 0.01; //Getting volume
    presetVolume = volume; //Sets the preset volume to the volume the user has set (this is for fade in and out)
    ifpress = settings.getPress();
    ifplaylist = settings.getPlaylist();
    if(ifplaylist)
    {
    on_actionPlaylist_Mode_triggered();
    }else{
    on_actionSoundBoard_Mode_triggered();
    }
    Samplerate = settings.getSampleRate();
    ifRandom = settings.getRandom();
    fade = settings.getFade() * 0.00001;
    ifNoDial = settings.getNoDial();

    BASS_SetDevice(device);
    BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, volume);
    //BASS_SetVolume(volume); //Setting volume
    BASS_SetDevice(device1);
    BASS_ChannelSetAttribute(stream1, BASS_ATTRIB_VOL, volume);
    //BASS_SetVolume(volume); //Setting volume
    BASS_SetDevice(device2);
    BASS_ChannelSetAttribute(stream2, BASS_ATTRIB_VOL, volume);
    //BASS_SetVolume(volume); //Setting volume
}

void MainWindow::setVolume(int value)
{
    if(value == -1)
    {
        BASS_SetDevice(device);
        BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, volume);
        //BASS_SetVolume(volume); //Setting volume
        BASS_SetDevice(device1);
        BASS_ChannelSetAttribute(stream1, BASS_ATTRIB_VOL, volume);
        //BASS_SetVolume(volume); //Setting volume
        BASS_SetDevice(device2);
        BASS_ChannelSetAttribute(stream2, BASS_ATTRIB_VOL, volume);
    }else{
        volume = value;
        BASS_SetDevice(device);
        BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, value);
        //BASS_SetVolume(volume); //Setting volume
        BASS_SetDevice(device1);
        BASS_ChannelSetAttribute(stream1, BASS_ATTRIB_VOL, value);
        //BASS_SetVolume(volume); //Setting volume
        BASS_SetDevice(device2);
        BASS_ChannelSetAttribute(stream2, BASS_ATTRIB_VOL, value);
    }
}

void MainWindow::setStatus() //Bug: When telephone buttons are pressed, the fade out happens.
{
    if(ifDebug == false) //This is where the time is set
    {
    currentTime = QTime::currentTime().toString();
    }

    if(buttons1.count() > 0)
    {
        for(int a = 0; a < buttons1.count(); a++)
        {
            if(currentTime == timePreset[buttons1.at(a)->toolTip()].at(1)) //currentTime.contains(timePreset[buttons1.at(a)->toolTip()].at(1))
            {
                if(!(ifOnce)) //Only allowing once
                {
                    ifOnce = true;
                    currentTimePreset = timePreset[buttons1.at(a)->toolTip()].at(0);
                    temp = current_song_number;
                    if(ifNoDial == false)
                    {
                    current_song_number = -2; //Fix this, this is due to the for loop not breaking and making it -2
                    on_intercomAll_Button_clicked();
                    }else{
                        isFade = true;
                        fadeChange = fade;
                        volume = 0;
                        if(ifRandom == true)
                        {
                            if(buttons.size() > 0)
                            on_random_Button_clicked();
                        }else{
                            current_song_number = temp;
                            if(buttons.size() > 0)
                            playList();
                        }
                    }
                    break;
                }
            }
            if(currentTime == timePreset[buttons1.at(a)->toolTip()].at(2))
            {
                //if(!(ifOnce)) Implement this in the future! because debug is breaks it to -3
                //{
                fadeChange = -(fade);
                isFade = true;
                currentTimePreset = "NULL";
                break;
                //}
            }
        }
    }

    if(isFade == true)
    {
        volume = volume + fadeChange;
        setVolume(-1);
        if(volume >= presetVolume)
        {
            isFade = false;
            ifOnce = false;
            return;
        }
        if(volume <= 0)
        {
            isFade = false;
            temp = current_song_number;
            //on_Stop_Button_clicked();
            current_song_number = -3;
            if(ifNoDial == false)
            {
            on_intercomCancel_Button_clicked();
            }else{
                on_Stop_Button_clicked();
                current_song_number = temp;
            }
            return;
        }
    }

    if(BASS_ChannelIsActive(stream))
    {
    const double time = BASS_ChannelBytes2Seconds(stream, BASS_ChannelGetPosition(stream, BASS_POS_BYTE)); //Gets the time data
    const double maxitime = BASS_ChannelBytes2Seconds(stream, BASS_ChannelGetLength(stream, BASS_POS_BYTE)); //Get the max time data
    QString artist;
    QString title;

    if(current_song_number > -1) //This crashes alot
    {
    TagLib::FileRef f(buttons.at(current_song_number)->toolTip().toStdString().c_str());
    title = QString::fromStdString(f.tag()->title().to8Bit());
    artist = QString::fromStdString(f.tag()->artist().to8Bit());
    }

    if(ifplaylist == true && current_song_number == 0)
    {
        ui->Previous_Button->setEnabled(false);
    }else if(ifplaylist == true && current_song_number == buttons.size() - 1)
    {
        ui->Next_Button->setEnabled(false);
    }

    if(time + 0.1 > maxitime)
    {
        ui->Next_Button->setDisabled(true);
        ui->Previous_Button->setDisabled(true);
        if(current_song_number == -1) //Make sure current_song_number isn't -2 or less or else it will crash
        {

        }else if(current_song_number == -2)
        {
            isFade = true;
            fadeChange = fade;
            volume = 0;
            if(ifRandom == true)
            {
                if(buttons.size() > 0)
                on_random_Button_clicked();
            }else{
                current_song_number = temp;
                if(buttons.size() > 0)
                playList();
            }
        }else if(current_song_number == -3){
            on_Stop_Button_clicked();
            current_song_number = temp;
            return;
        }else if(ifplaylist == true && current_song_number < buttons.size() - 1)
        {
            if(ifRandom == true)
            {
                if(buttons.size() > 0)
                on_random_Button_clicked();
            }else{
                if(buttons.size() > 0)
                playList();
            }
        }
    }

    if(ifplaylist == true && current_song_number == -1)
    {
        current_song_number = buttons.indexOf(current);
    }

    statusLabel = "Currently Playing [Title: " + title + " Artist: " + artist + " Time: " + QTime::fromMSecsSinceStartOfDay(time*1000).toString("mm:ss") + "/" + QTime::fromMSecsSinceStartOfDay(maxitime*1000).toString("mm:ss") + "]" + " Current Time: [" + currentTime
            + "] Current Time Preset: [" + currentTimePreset + "]";

    ui->Status_Label->setText(statusLabel);

    if(noblemove > 6)
    {
        this->setWindowTitle(statusLabel);
    }

    DWORD level, leftc, rightc;

    level = BASS_ChannelGetLevel(stream);
    leftc = LOWORD(level);
    rightc = HIWORD(level);
    ui->VU_Meter->setValue(leftc * 0.001);
    ui->VU_Meter_2->setValue(rightc * 0.001);

    ui->Time_Slider->setValue(time * 10000);
    }else{
        ui->Time_Slider->setValue(0);
        ui->Time_Slider->setMaximum(100);
        ui->Pause_Button->setDisabled(true);
        ui->Stop_Button->setDisabled(true);
        ui->Time_Slider->setDisabled(true); //Disabling Slider
        ui->Status_Label->setText("Currently Playing [NULL] Current Time: [" + currentTime + "]");
    }
}

void MainWindow::on_Stop_Button_clicked()
{
    if(BASS_ChannelIsActive(stream))
    {
    ifOnce = false;
    current_song_number = -1;
    //isFade = false;
    BASS_Free();
    BASS_SetDevice(device);
    BASS_Free();
    BASS_SetDevice(device1);
    BASS_Free();
    BASS_SetDevice(device2);
    ui->Time_Slider->setValue(0);
    ui->Time_Slider->setMaximum(100);
    ui->Pause_Button->setDisabled(true);
    ui->Stop_Button->setDisabled(true);
    ui->Time_Slider->setDisabled(true); //Disabling Slider
    ui->Next_Button->setDisabled(true);
    ui->Previous_Button->setDisabled(true);
    ui->Status_Label->setText("Currently Playing [NULL]");
    }
}

void MainWindow::on_Pause_Button_clicked()
{
    if(ifpause)
    {
        ui->Pause_Button->setText("Pause");
        BASS_ChannelPlay(stream, false);
        BASS_ChannelPlay(stream1, false);
        BASS_ChannelPlay(stream2, false);
        ifpause = false;
    }else{
        ui->Pause_Button->setText("Play");
        BASS_ChannelPause(stream);
        BASS_ChannelPause(stream1);
        BASS_ChannelPause(stream2);
        ifpause = true;
    }
}

void MainWindow::on_Remove_Button_clicked()
{
    if(ifremove)
    {
        ui->Remove_Button->setText("Remove");
        ifremove = false;
    }else{
        ui->Remove_Button->setText("Cancel");
        ifremove = true;
    }
}

void MainWindow::on_Time_Slider_sliderMoved(int position)
{
    BASS_ChannelSetPosition(stream, BASS_ChannelSeconds2Bytes(stream, position * 0.0001), BASS_POS_BYTE);
    BASS_ChannelSetPosition(stream1, BASS_ChannelSeconds2Bytes(stream1, position * 0.0001), BASS_POS_BYTE);
    BASS_ChannelSetPosition(stream2, BASS_ChannelSeconds2Bytes(stream2, position * 0.0001), BASS_POS_BYTE);
}

void MainWindow::on_Time_Slider_sliderPressed()
{
    BASS_ChannelPause(stream);
    BASS_ChannelPause(stream1);
    BASS_ChannelPause(stream2);
    timer->stop();
}

void MainWindow::on_Time_Slider_sliderReleased()
{
    BASS_ChannelPlay(stream, false);
    BASS_ChannelPlay(stream1, false);
    BASS_ChannelPlay(stream2, false);
    timer->start(10);
}

void MainWindow::on_actionSave_Preset_triggered() //Where preset xml gets written
{
    QString filename = QFileDialog::getSaveFileName(this, "Save File", "C:\\", "XML (*.xml)");

    QFile file(filename);
    file.open(QFile::ReadWrite);

    QXmlStreamWriter writer(&file);

    writer.setAutoFormatting(true);

    writer.writeStartDocument();

    writer.writeStartElement("SoundBoard");

    writer.writeStartElement("Setting");

    writer.writeTextElement("Mode", QString::number(Mode));

    writer.writeTextElement("Volume", QString::number(volume));

    writer.writeTextElement("Press", QString::number(ifpress));

    writer.writeTextElement("Playlist", QString::number(ifplaylist));

    writer.writeTextElement("Samplerate", QString::number(Samplerate));

    writer.writeTextElement("Random", QString::number(ifRandom));

    writer.writeTextElement("Fade", QString::number(fade));

    writer.writeTextElement("Nodial", QString::number(ifNoDial));

    writer.writeStartElement("Devices");

    writer.writeTextElement("Device_0", QString::number(device));

    writer.writeTextElement("Device_1", QString::number(device1));

    writer.writeTextElement("Device_2", QString::number(device2));

    writer.writeEndElement();

    writer.writeEndElement();

    writer.writeStartElement("Audio_Button");

    for(int a = 0; a < buttons.size(); a++)
    {
        writer.writeStartElement("Button" + QString::number(a));
        writer.writeTextElement("File_Name", buttons.at(a)->text());
        writer.writeTextElement("File_Dir", buttons.at(a)->toolTip());
        writer.writeEndElement();
    }

    writer.writeEndElement();

    writer.writeStartElement("Time_Preset");

    for(int a = 0; a < buttons1.size(); a++)
    {
        writer.writeStartElement("Button" + QString::number(a));
        writer.writeTextElement("Name", timePreset[buttons1.at(a)->toolTip()].at(0));
        writer.writeTextElement("Start_Time", timePreset[buttons1.at(a)->toolTip()].at(1));
        writer.writeTextElement("End_Time", timePreset[buttons1.at(a)->toolTip()].at(2));
        writer.writeTextElement("Volume", timePreset[buttons1.at(a)->toolTip()].at(3));
        writer.writeTextElement("Fade", timePreset[buttons1.at(a)->toolTip()].at(4));
        writer.writeEndElement();
    }

    writer.writeEndElement();

    writer.writeEndDocument();

    file.close();
}

void MainWindow::on_actionOpen_Preset_triggered() //Where xml file is read
{
    QString file_name = QFileDialog::getOpenFileName(this, tr("Open file"), tr("C:\\"), tr("XML (*.xml)"));

    QFile file(file_name);

    if(file.open(QIODevice::ReadOnly))
    {
    QXmlStreamReader reader(&file);
    reader.readNext();

    if(reader.readNextStartElement()) //Root
    {
    while(reader.readNextStartElement())
    {
        if(reader.name() == "Setting")
        {
            while(reader.readNextStartElement())
            {
                if(reader.name() == "Mode")
                {
                    Mode = reader.readElementText().toInt();
                    if(Mode == 1)
                        on_actionPlaylist_Mode_triggered();
                }
                if(reader.name() == "Volume")
                {
                    volume = reader.readElementText().toDouble();
                    BASS_SetDevice(device);
                    BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, volume);
                    //BASS_SetVolume(volume); //Setting volume
                    BASS_SetDevice(device1);
                    BASS_ChannelSetAttribute(stream1, BASS_ATTRIB_VOL, volume);
                    //BASS_SetVolume(volume); //Setting volume
                    BASS_SetDevice(device2);
                    BASS_ChannelSetAttribute(stream2, BASS_ATTRIB_VOL, volume);
                    //BASS_SetVolume(volume); //Setting volume
                }
                if(reader.name() == "Press")
                {
                    ifpress = reader.readElementText().toInt();
                }
                if(reader.name() == "Playlist")
                {
                    ifplaylist = reader.readElementText().toInt();
                }
                if(reader.name() == "Samplerate")
                {
                    Samplerate = reader.readElementText().toInt();
                }
                if(reader.name() == "Random")
                {
                    ifRandom = reader.readElementText().toInt();
                }
                if(reader.name() == "Fade")
                {
                    fade = reader.readElementText().toDouble();
                }
                if(reader.name() == "Nodial")
                {
                    ifNoDial = reader.readElementText().toInt();
                }
                if(reader.name() == "Devices")
                {
                    while(reader.readNextStartElement())
                    {
                        if(reader.name() == "Device_0")
                        {
                            device = reader.readElementText().toInt();
                        }
                        if(reader.name() == "Device_1")
                        {
                            device1 = reader.readElementText().toInt();
                        }
                        if(reader.name() == "Device_2")
                        {
                            device2 = reader.readElementText().toInt();
                        }
                    }
                }
            }
        }
        if(reader.name() == "Audio_Button")
        {
            while(reader.readNextStartElement())
            {
                QPushButton *button = new QPushButton;
                while(reader.readNextStartElement())
                {
                    if(reader.name() == "File_Name")
                    {
                        button->setText(reader.readElementText());
                    }
                    if(reader.name() == "File_Dir")
                    {
                        button->setToolTip(reader.readElementText());
                    }
                }
                layout->addWidget(button);
                buttons.append(button);
                ui->scrollArea->setWidget(widget);
                connect(button, SIGNAL(pressed()), this, SLOT(on_Button_Clicked()));
            }
        }
        if(reader.name() == "Time_Preset")
        {
            while(reader.readNextStartElement())
            {
                QPushButton *button = new QPushButton;
                QList<QString> list;
                while(reader.readNextStartElement())
                {
                    if(reader.name() == "Name")
                    {
                        list.append(reader.readElementText());
                    }
                    if(reader.name() == "Start_Time")
                    {
                        list.append(reader.readElementText());
                    }
                    if(reader.name() == "End_Time")
                    {
                        list.append(reader.readElementText());
                    }
                    if(reader.name() == "Volume")
                    {
                        list.append(reader.readElementText());
                    }
                    if(reader.name() == "Fade")
                    {
                        list.append(reader.readElementText());
                    }
                }
                button->setText("Name: " + list.at(0) + " Start Time: " + list.at(1) + " End Time: " + list.at(2));
                button->setToolTip(list.at(0));
                layout1->addWidget(button);
                buttons1.append(button);
                timePreset[list.at(0)] = list;
                ui->scrollArea_2->setWidget(widget1);
                //connect(button, SIGNAL(pressed()), this, SLOT(on_Button_Clicked()));
            }
        }
    }
    }
    }
    file.close();
}

void MainWindow::on_Secret_Button_clicked()
{
    noblemove++;
    if(noblemove == 1)
    {
        ui->debugEnable_checkBox->setEnabled(true);
        ui->debugEnable_checkBox->setVisible(true);
        ui->debug_timeEdit->setEnabled(true);
        ui->debug_timeEdit->setVisible(true);
    }
    if(noblemove == 3)
    {
        ui->Speed_Slider->setVisible(true);
        ui->Speed_Slider->setEnabled(true);
    }
    if(noblemove == 6)
    {
        QMessageBox box;
        box.setWindowTitle("#NOBLEMOVE");
        box.setText("#NOBLEMOVE IS AMAZING");
        box.setInformativeText("#NOBLEMOVE has been activated!");
        box.addButton(tr("Ban Boom"), QMessageBox::YesRole);
        box.addButton(tr("Ban ha0511kr"), QMessageBox::YesRole);
        box.exec();
        ui->VU_Meter->setEnabled(true);
        ui->VU_Meter_2->setEnabled(true);
        ui->VU_Meter->setVisible(true);
        ui->VU_Meter_2->setVisible(true);
    }else if(noblemove == 13)
    {
        E_Button = new Extra_Button;
        E_Button->exec();
    }
}

void MainWindow::on_Speed_Slider_sliderMoved(int position)
{
    BASS_SetDevice(device);
    BASS_ChannelSetAttribute(stream, BASS_ATTRIB_MUSIC_SPEED, position);
}

void MainWindow::on_actionSoundBoard_Mode_triggered()
{
    Mode = 0;
    ifplaylist = false;
    ui->Next_Button->setVisible(false);
    ui->Previous_Button->setVisible(false);
    ui->EPlaylist_Button->setVisible(false);
    ui->random_Button->setVisible(false);
    ui->Next_Button->setDisabled(true);
    ui->Previous_Button->setDisabled(true);
    ui->EPlaylist_Button->setDisabled(true);
    ui->random_Button->setDisabled(true);
}

void MainWindow::on_actionPlaylist_Mode_triggered()
{
    Mode = 1;
    ifplaylist = true;
    ui->Next_Button->setVisible(true);
    ui->Previous_Button->setVisible(true);
    ui->EPlaylist_Button->setVisible(true);
    ui->random_Button->setVisible(true);
    ui->EPlaylist_Button->setEnabled(true);
}

void MainWindow::on_Next_Button_clicked()
{
    if(ifplaylist == true && ifedit == false && current_song_number < buttons.size() - 1)
    {
    on_Button_Clicked();
    }else{
    int getCurrentButtonNum = buttons.indexOf(editcurrent);
    if(getCurrentButtonNum > 0)
    {
    QPushButton *button = buttons.at(getCurrentButtonNum);
    QPushButton *lastbutton = buttons.at(getCurrentButtonNum - 1);
    QString first = button->text();
    QString second = lastbutton->text();
    QString first_dir = button->toolTip();
    QString second_dir = lastbutton->toolTip();

    lastbutton->setText(first);
    button->setText(second);

    lastbutton->setToolTip(first_dir);
    button->setToolTip(second_dir);

    editcurrent = lastbutton;

    buttons.push_back(button);
    }
    }
}

void MainWindow::on_Previous_Button_clicked()
{
    if(ifplaylist == true && ifedit == false && current_song_number > 0)
    {
    on_Button_Clicked();
    }else{
        int getCurrentButtonNum = buttons.indexOf(editcurrent);
    if(getCurrentButtonNum < buttons.size() - 1)
    {
    QPushButton *button = buttons.at(getCurrentButtonNum);
    QPushButton *fowardbutton = buttons.at(getCurrentButtonNum + 1);
    QString first = button->text();
    QString second = fowardbutton->text();
    QString first_dir = button->toolTip();
    QString second_dir = fowardbutton->toolTip();

    fowardbutton->setText(first);
    button->setText(second);

    fowardbutton->setToolTip(first_dir);
    button->setToolTip(second_dir);

    editcurrent = fowardbutton;
    }
    }
}

void MainWindow::on_EPlaylist_Button_clicked()
{
    if(ifedit == false)
    {
        ui->Next_Button->setText("Move Up");
        ui->Previous_Button->setText("Move Down");
        ui->EPlaylist_Button->setText("Select Button");
        ui->Status_Label->setText("Selected Button: ");
        ui->Next_Button->setDisabled(true);
        ui->Previous_Button->setDisabled(true);
        timer->stop();
        ifedit = true;
    }else{
        ui->Next_Button->setText("Next");
        ui->Previous_Button->setText("Previous");
        ui->EPlaylist_Button->setText("Edit Playlist");
        ui->Next_Button->setDisabled(true);
        ui->Previous_Button->setDisabled(true);
        timer->start(10);
        ifedit = false;
    }
}

void MainWindow::on_actionInsert_Sound_triggered()
{
    on_ISound_Button_clicked();
}

void MainWindow::on_one_Button_clicked()
{
    current_song_number = -1;
    playSound("./Generated Tones/1.wav");

    /*LPHLINEAPP line;
    HINSTANCE                hInstance;
    LINECALLBACK             lpfnCallback;
    LPDWORD                  lpdwNumDevs;
    LPDWORD                  lpdwAPIVersion;
    LPLINEINITIALIZEEXPARAMS lpLineInitializeExParams;
    lineInitializeEx(line, hInstance, lpfnCallback, NULL, lpdwNumDevs, lpdwAPIVersion, lpLineInitializeExParams);*/
}

void MainWindow::on_two_Button_clicked()
{
    current_song_number = -1;
    playSound("./Generated Tones/2.wav");
}

void MainWindow::on_three_Button_clicked()
{
    current_song_number = -1;
    playSound("./Generated Tones/3.wav");
}

void MainWindow::on_four_Button_clicked()
{
    current_song_number = -1;
    playSound("./Generated Tones/4.wav");
}

void MainWindow::on_five_Button_clicked()
{
    current_song_number = -1;
    playSound("./Generated Tones/5.wav");
}

void MainWindow::on_six_Button_clicked()
{
    current_song_number = -1;
    playSound("./Generated Tones/6.wav");
}

void MainWindow::on_seven_Button_clicked()
{
    current_song_number = -1;
    playSound("./Generated Tones/7.wav");
}

void MainWindow::on_eight_Button_clicked()
{
    current_song_number = -1;
    playSound("./Generated Tones/8.wav");
}

void MainWindow::on_nine_Button_clicked()
{
    current_song_number = -1;
    playSound("./Generated Tones/9.wav");
}

void MainWindow::on_asterisk_Button_clicked()
{
    current_song_number = -1;
    playSound("./Generated Tones/s.wav");
}

void MainWindow::on_zero_Button_clicked()
{
    current_song_number = -1;
    playSound("./Generated Tones/0.wav");
}

void MainWindow::on_hash_Button_clicked()
{
    current_song_number = -1;
    playSound("./Generated Tones/p.wav");
}

void MainWindow::on_intercomOn_Button_clicked()
{
    playSound("./Generated Tones/Play_0.wav");
}

void MainWindow::on_intercomAll_Button_clicked()
{
    playSound("./Generated Tones/All_0.wav");
}

void MainWindow::on_intercomCancel_Button_clicked()
{
    playSound("./Generated Tones/Cancel_0.wav");
}

void MainWindow::on_addTime_Button_clicked()
{
    addTime time;
    //time.setTime();
    if(time.exec() == QDialog::Accepted)
    {
    QString name = time.getName();
    if(name == "")
    {
        return;
    }
    QTime startTime = time.getStartTime();
    QTime endTime = time.getEndTime();
    int volume = time.getVolume();
    bool fade = time.getFadeInOut();
    QList<QString> list;
    list.append(name);
    list.append(startTime.toString());
    list.append(endTime.toString());
    list.append(QString::number(volume));
    list.append(QString::number(fade));
    timePreset[name] = list;
    QPushButton *button = new QPushButton("Name: " + name + " Start Time: " + startTime.toString() + " End Time: " + endTime.toString());
    button->setToolTip(name);
    layout1->addWidget(button);
    buttons1.append(button);
    connect(button, SIGNAL(clicked(bool)), this, SLOT(on_timeButton_Clicked()));
    ui->scrollArea_2->setWidget(widget1);
    num_TimeButton++;
    }
}

void MainWindow::on_timeButton_Clicked()
{
    on_addTime_Button_clicked();
}

void MainWindow::on_random_Button_clicked()
{
    srand(time(NULL));
    int index = rand() % buttons.size();
    QPushButton *tempButton = buttons.at(index);
    playSound(tempButton->toolTip());
    current = tempButton;
    current_song_number = index;
    ui->Next_Button->setEnabled(true);
    ui->Previous_Button->setEnabled(true);
}

void MainWindow::on_debug_timeEdit_editingFinished()
{
    currentTime = ui->debug_timeEdit->time().toString();
}

void MainWindow::on_debugEnable_checkBox_clicked(bool checked)
{
    ifDebug = checked;
}
