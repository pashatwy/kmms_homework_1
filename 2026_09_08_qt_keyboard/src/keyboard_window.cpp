#include "keyboard_window.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>

using biv::KeyBoardWindow;

KeyBoardWindow::KeyBoardWindow(QWidget* parent) : QWidget(parent) {
	const int keyboard_width = 1160;
	resize(keyboard_width, 710);
    setWindowTitle("Грустная Клавиатура");
	
	QPixmap pixmap("img/grustnii-smail.png");
	QLabel* image = new QLabel(this);
	image->setFixedSize(200, 200);
	image->setPixmap(pixmap);
	image->setScaledContents(true);
	
	QHBoxLayout* smail_layout = new QHBoxLayout();
	smail_layout->addWidget(image);

    display = new QLineEdit();
	display->setMinimumHeight(80);
	display->setFont(QFont("Roboto", 40));
    display->setReadOnly(true);
	display->setFocusPolicy(Qt::NoFocus);
	display->setText("Помоги мне заработать лучше...");

	keyboard = new KeyBoard(keyboard_width);
	
	connect(keyboard, &KeyBoard::key_clicked, this, [this](const QString& text) {
		display->setText( display->text() + text );
	});
	
	connect(keyboard, &KeyBoard::backspace_clicked, this, [this]() {
		QString current = display->text();
		current.chop(1);
		display->setText(current);
	});

    QVBoxLayout* main_layout = new QVBoxLayout(this);
	main_layout->addLayout(smail_layout);
    main_layout->addWidget(display);
    main_layout->addWidget(keyboard);
}

void KeyBoardWindow::keyPressEvent(QKeyEvent* event) {
	if (keyboard->is_special_key(event->key())) {
		keyboard->animate_special_button(event->key());
		return;
	}
	const int key = event->nativeVirtualKey();
	if (keyboard->is_key_allowed(key)) {
		keyboard->animate_button(key);
	}
}
