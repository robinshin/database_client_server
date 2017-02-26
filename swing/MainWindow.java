import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

public class MainWindow extends JFrame {
	private static final long serialVersionUID = 1L;
	private JTextArea textArea;
	private JTextField textField;
	private JRadioButton buttonPhoto;
	private JRadioButton buttonVideo;
	private JRadioButton buttonFilm;
	private JRadioButton buttonGroup;
	private JButton buttonSend;
	private ButtonGroup bg;
	private JTabbedPane tabbedPanel;
	private JPanel panelAdd;
	private JPanel panelDelete;
	private JPanel panelFind;
	private JPanel panelPlay;
	private JScrollPane scrollPane;
	private JMenu menu;
	private JMenuBar menuBar;
	private MenuButton endMenuButton;


	private String action = "Ajouter"; // Car l'onglet ouvert par défaut est l'onglet "Ajouter"
	private String type = "";
	private String fileName = "";

	private Client client;
	private String request, response;

	public MainWindow() {
		//////// Initialisation du client
		client = null;

		try {
			client = new Client("localhost", 3331);
		}
		catch (Exception e) {
			System.err.println("Client: Couldn't connect to "+"localhost"+":"+3331);
			System.exit(1);
		}

		System.out.println("Client connected to "+"localhost"+":"+3331);


		//////// Initialisation de la vue
		this.setTitle("Fenêtre principale");
		this.setLocationRelativeTo(null);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);


		//////// Initialisation des attributs
		textArea = new JTextArea(30, 40);
		textField = new JTextField("Entrer le nom du fichier", 20);
		scrollPane = new JScrollPane(textArea);
		buttonPhoto = new JRadioButton("Photo");
		buttonVideo = new JRadioButton("Video");
		buttonFilm = new JRadioButton("Film");
		buttonGroup = new JRadioButton("Groupe");
		buttonSend = new JButton("Envoyer la requête");
		tabbedPanel = new JTabbedPane();
		panelAdd = new JPanel();
		panelDelete = new JPanel();
		panelFind = new JPanel();
		panelPlay = new JPanel();
		menu = new JMenu("Menu");
		menuBar = new JMenuBar();
		endMenuButton = new MenuButton("Quitter");


		//// Simultanéité des boutons
		bg = new ButtonGroup();
		bg.add(buttonPhoto);
		bg.add(buttonVideo);
		bg.add(buttonFilm);
		bg.add(buttonGroup);


		this.setPanel();
		this.setTabbedPanel();
		this.setMenu();
		this.setMenuBar();
		this.setJMenuBar(menuBar);
		this.setButtonListeners();

		this.setTabbedPanelListeners();


		this.getContentPane().add(tabbedPanel, BorderLayout.SOUTH);
		this.getContentPane().add(scrollPane, BorderLayout.CENTER);
		this.getContentPane().add(menuBar, BorderLayout.NORTH);
		System.setProperty("apple.laf.useScreenMenuBar", "true");
		this.pack();
		this.setVisible(true);
	}

	private void setPanel() {
		panelAdd.setName("Ajouter");
		panelDelete.setName("Supprimer");
		panelFind.setName("Rechercher");
		panelPlay.setName("Jouer");

		panelAdd.add(buttonPhoto);
		panelAdd.add(buttonVideo);
		panelAdd.add(buttonFilm);
		panelAdd.add(buttonGroup);
		panelAdd.add(textField);
		panelAdd.add(buttonSend);
	}

	private void setTabbedPanel() {
		tabbedPanel.add(panelAdd, 0);
		tabbedPanel.add(panelDelete, 1);
		tabbedPanel.add(panelFind, 2);
		tabbedPanel.add(panelPlay, 3);
	}

	private void setMenu() {
		menu.add(endMenuButton);
	}

	private void setMenuBar() {
		menuBar.add(menu);
		menuBar.setVisible(true);
	}

	private void setButtonListeners() {
		ActionListener buttonListener = new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if (buttonPhoto.isSelected())
					type = "Photo";
				else if (buttonVideo.isSelected())
					type = "Video";
				else if (buttonFilm.isSelected())
					type = "Film";
				else if (buttonGroup.isSelected())
					type = "Groupe";
			}
		};
		buttonPhoto.addActionListener(buttonListener);
		buttonVideo.addActionListener(buttonListener);
		buttonFilm.addActionListener(buttonListener);
		buttonGroup.addActionListener(buttonListener);

		ActionListener sendButtonListener = new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if (((tabbedPanel.getSelectedIndex() == 0) || (tabbedPanel.getSelectedIndex() == 1)) && ((!buttonPhoto.isSelected()) && (!buttonVideo.isSelected()) && (!buttonFilm.isSelected()) && (!buttonGroup.isSelected()))) {
					JOptionPane.showMessageDialog(null, "Veuillez choisir un type de fichier", "Attention", JOptionPane.WARNING_MESSAGE);
				}
				else if (textField.getText().compareTo("Entrer le nom du fichier") == 0) {
					JOptionPane.showMessageDialog(null, "Veuillez remplir le nom du fichier", "Attention", JOptionPane.WARNING_MESSAGE);
				}
				else {
					fileName = textField.getText();
					if ((tabbedPanel.getSelectedIndex() == 0) || (tabbedPanel.getSelectedIndex() == 1))
						request = action + " " + type + " " + fileName;
					else
						request = action + " " + fileName;
					
					textArea.append(">>>>>> Requête : " + request + '\n');
					response = client.send(request);
					textArea.append(">>> Réponse : " + response + '\n' + '\n');
					textField.setText("Entrer le nom du fichier");
					bg.clearSelection();
				}
			}
		};
		buttonSend.addActionListener(sendButtonListener);
	}

	private void setTabbedPanelListeners() {
		tabbedPanel.addChangeListener(new ChangeListener() {
			@Override
			public void stateChanged(ChangeEvent e) {
				switch(tabbedPanel.getSelectedIndex()){
				case 0:
					action = "Ajouter";
					textField.setColumns(20);
					textField.setText("Entrer le nom du fichier");
					bg.clearSelection();
					panelAdd.add(buttonPhoto);
					panelAdd.add(buttonVideo);
					panelAdd.add(buttonFilm);
					panelAdd.add(buttonGroup);
					panelAdd.add(textField);
					panelAdd.add(buttonSend);
					break;
				case 1: 
					action = "Supprimer";
					textField.setColumns(20);
					textField.setText("Entrer le nom du fichier");
					bg.clearSelection();
					panelDelete.add(buttonPhoto);
					panelDelete.add(buttonVideo);
					panelDelete.add(buttonFilm);
					panelDelete.add(buttonGroup);
					panelDelete.add(textField);
					panelDelete.add(buttonSend);
					break;
				case 2:
					action = "Rechercher";
					textField.setColumns(40);
					textField.setText("Entrer le nom du fichier");
					panelFind.add(textField);
					panelFind.add(buttonSend);
					break;
				case 3:
					action = "Jouer";
					textField.setText("Entrer le nom du fichier");
					textField.setColumns(40);
					panelPlay.add(textField);
					panelPlay.add(buttonSend);
					break;
				}
			}
		});
	}


	private class MenuButton extends AbstractAction {
		private static final long serialVersionUID = 1L;

		public MenuButton(String name){
			super(name);
		}

		@Override
		public void actionPerformed(ActionEvent e) {
			System.exit(0);
		}

	}
}
