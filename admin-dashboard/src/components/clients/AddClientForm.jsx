import { useState } from 'react'
import { useNavigate } from 'react-router-dom'; // Hook para redirección

const AddClientForm = () => {
    const [formData, setFormData] = useState({
        nombre: '',
        cuit: '',
        razon_social: '',
        tributacion: 'Responsable Inscripto',
        telefono: '',
        email: '',
        direccion_fiscal: '',
        direccion_entrega: '',
        localidad: '',
        cp: '',
        whatsapp: '',
    });

    const navigate = useNavigate();

    const handleChange = (e) => {
        const { name, value } = e.target;
        setFormData((prevData) => ({
            ...prevData,
            [name]: value,
        }));
    };

    const handleSubmit = async (e) => {
        e.preventDefault();
        console.log('Datos del cliente:', formData);
        try {
            const response = await fetch('http://localhost:9080/clientes', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify(formData),
            });

            if (response.ok) {
                alert('Cliente creado exitosamente!');
                navigate('/clients'); // Redirige a la lista de clientes
            } else {
                const errorData = await response.json();
                console.error('Error en la creación:', errorData);
                alert('Hubo un error al crear el cliente. Verifique los datos.');
            }
        } catch (error) {
            console.error('Error en la solicitud:', error);
            alert('Ocurrió un error al conectar con el servidor.');
        }
    };

    return (
        <div className="max-w-4xl mx-auto mt-10 p-6  rounded-lg h-screen overflow-y-auto" >
            <h2 className="text-2xl font-semibold text-white mb-4">Agregar Cliente</h2>
            <form onSubmit={handleSubmit} className="grid grid-cols-1 md:grid-cols-2 gap-6">
                <div>
                    <label className="block text-white mb-2">Nombre</label>
                    <input
                        type="text"
                        name="nombre"
                        value={formData.nombre}
                        onChange={handleChange}
                        className="w-full p-2 rounded bg-gray-700 text-white"
                        required
                    />
                </div>

                <div>
                    <label className="block text-white mb-2">CUIT</label>
                    <input
                        type="text"
                        name="cuit"
                        value={formData.cuit}
                        onChange={handleChange}
                        className="w-full p-2 rounded bg-gray-700 text-white"
                        required
                    />
                </div>

                <div>
                    <label className="block text-white mb-2">Razón Social</label>
                    <input
                        type="text"
                        name="razon_social"
                        value={formData.razon_social}
                        onChange={handleChange}
                        className="w-full p-2 rounded bg-gray-700 text-white"
                        required
                    />
                </div>

                <div>
                    <label className="block text-white mb-2">Tributación</label>
                    <select
                        name="tributacion"
                        value={formData.tributacion}
                        onChange={handleChange}
                        className="w-full p-2 rounded bg-gray-700 text-white"
                        required
                    >
                        <option value="Responsable Inscripto">Responsable Inscripto</option>
                        <option value="Monotributista">Monotributista</option>
                        <option value="Exento">Exento</option>
                    </select>
                </div>

                <div>
                    <label className="block text-white mb-2">Teléfono</label>
                    <input
                        type="tel"
                        name="telefono"
                        value={formData.telefono}
                        onChange={handleChange}
                        className="w-full p-2 rounded bg-gray-700 text-white"
                        required
                    />
                </div>

                <div>
                    <label className="block text-white mb-2">Email</label>
                    <input
                        type="email"
                        name="email"
                        value={formData.email}
                        onChange={handleChange}
                        className="w-full p-2 rounded bg-gray-700 text-white"
                        required
                    />
                </div>

                <div>
                    <label className="block text-white mb-2">Dirección Fiscal</label>
                    <input
                        type="text"
                        name="direccion_fiscal"
                        value={formData.direccion_fiscal}
                        onChange={handleChange}
                        className="w-full p-2 rounded bg-gray-700 text-white"
                        required
                    />
                </div>

                <div>
                    <label className="block text-white mb-2">Dirección de Entrega</label>
                    <input
                        type="text"
                        name="direccion_entrega"
                        value={formData.direccion_entrega}
                        onChange={handleChange}
                        className="w-full p-2 rounded bg-gray-700 text-white"
                        required
                    />
                </div>

                <div>
                    <label className="block text-white mb-2">Localidad</label>
                    <input
                        type="text"
                        name="localidad"
                        value={formData.localidad}
                        onChange={handleChange}
                        className="w-full p-2 rounded bg-gray-700 text-white"
                        required
                    />
                </div>

                <div>
                    <label className="block text-white mb-2">Código Postal</label>
                    <input
                        type="text"
                        name="cp"
                        value={formData.cp}
                        onChange={handleChange}
                        className="w-full p-2 rounded bg-gray-700 text-white"
                        required
                    />
                </div>

                <div>
                    <label className="block text-white mb-2">WhatsApp</label>
                    <input
                        type="tel"
                        name="whatsapp"
                        value={formData.whatsapp}
                        onChange={handleChange}
                        className="w-full p-2 rounded bg-gray-700 text-white"
                        required
                    />
                </div>

                {/* Botón para enviar */}
                <div className="col-span-1 md:col-span-2">
                    <button
                        type="submit"
                        className="bg-blue-500 hover:bg-blue-700 text-white font-bold py-2 px-4 rounded w-full mt-4"
                    >
                        Agregar Cliente
                    </button>
                </div>
            </form>
        </div>
    );
};

export default AddClientForm;
