import { useState, useEffect } from 'react';
import { useNavigate, useLocation } from 'react-router-dom';

const EditProductForm = () => {
    const navigate = useNavigate();
    const { state } = useLocation(); // Recibe los datos del cliente
    const { product } = state || {};  // Asegura que haya datos disponibles

    const [formData, setFormData] = useState({
        sku: '',
        nombre: '',
        tipo_producto: '',
        stock_minimo: 0,
        stock_actual: 0,
        costo: 0.0,
        precio_venta: 0.0,
        precio_sin_iva: 0.0,
        precio_con_iva: 0.0,
        precio_minorista: 0.0,
        precio_mayorista: 0.0,
        precio_venta_minimo: 0.0,
    });

    useEffect(() => {
        if (product) {
            setFormData(product); // Autocompleta los campos con los datos del producto
        }
    }, [product]);

    const handleChange = (e) => {
        const { name, value } = e.target;
        setFormData((prevData) => ({
            ...prevData,
            [name]: value,
        }));
    };

    const handleSubmit = async (e) => {
        e.preventDefault();

        const formattedData = {
            ...formData,
            stock_minimo: parseInt(formData.stock_minimo, 10),
            stock_actual: parseInt(formData.stock_actual, 10),
            costo: parseFloat(formData.costo),
            precio_venta: parseFloat(formData.precio_venta),
            precio_sin_iva: parseFloat(formData.precio_sin_iva),
            precio_con_iva: parseFloat(formData.precio_con_iva),
            precio_minorista: parseFloat(formData.precio_minorista),
            precio_mayorista: parseFloat(formData.precio_mayorista),
            precio_venta_minimo: parseFloat(formData.precio_venta_minimo),
        };
        console.log(formattedData)
        try {
            const response = await fetch(`http://localhost:9080/productos/${product.id}`, {
                method: 'PUT',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify(formattedData),
            });

            if (response.ok) {
                alert('Producto actualizado exitosamente!');
                navigate('/products'); // Redirige a la lista de clientes
            } else {
                alert('Error al actualizar el producto.');
            }
        } catch (error) {
            console.error('Error en la actualización:', error);
            alert('Hubo un error al conectar con el servidor.');
        }
    };

    return (
        <div className="max-w-4xl mx-auto mt-10 p-6 rounded-lg h-screen overflow-y-auto relative z-10">
            <h2 className="text-2xl font-semibold text-white mb-4">Editar Cliente</h2>
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
                    <label className="block text-white mb-2">SKU</label>
                    <input
                        type="text"
                        name="sku"
                        value={formData.sku}
                        onChange={handleChange}
                        className="w-full p-2 rounded bg-gray-700 text-white"
                        required
                    />
                </div>

                <div>
                    <label className="block text-white mb-2">Tipo de Producto</label>
                    <select
                        name="tipo_producto"
                        value={formData.tipo_producto}
                        onChange={handleChange}
                        className="w-full p-2 rounded bg-gray-700 text-white"
                        required
                    >
                        <option value="Servicios">Servicios</option>
                        <option value="Insumos">Insumos</option>
                    </select>
                </div>

                <div>
                    <label className="block text-white mb-2">Stock minimo</label>
                    <input
                        type="number"
                        name="stock_minimo"
                        value={formData.stock_minimo}
                        onChange={handleChange}
                        className="w-full p-2 rounded bg-gray-700 text-white"
                        required
                    />
                </div>                

                <div>
                    <label className="block text-white mb-2">Stock Actual</label>
                    <input
                        type="number"
                        name="stock_actual"
                        value={formData.stock_actual}
                        onChange={handleChange}
                        className="w-full p-2 rounded bg-gray-700 text-white"
                        required
                    />
                </div>

                <div>
                    <label className="block text-white mb-2">Costo</label>
                    <input
                        type="number"
                        name="costo"
                        value={formData.costo.toFixed(2)}
                        onChange={handleChange}
                        className="w-full p-2 rounded bg-gray-700 text-white"
                        required
                    />
                </div>

                <div>
                    <label className="block text-white mb-2">Precio Venta</label>
                    <input
                        type="number"
                        name="precio_venta"
                        value={formData.precio_venta.toFixed(2)}
                        onChange={handleChange}
                        className="w-full p-2 rounded bg-gray-700 text-white"
                        required
                    />
                </div>

                <div>
                    <label className="block text-white mb-2">Precio sin IVA</label>
                    <input
                        type="number"
                        name="precio_sin_iva"
                        value={formData.precio_sin_iva.toFixed(2)}
                        onChange={handleChange}
                        className="w-full p-2 rounded bg-gray-700 text-white"
                        required
                    />
                </div>

                <div>
                    <label className="block text-white mb-2">Precio con IVA</label>
                    <input
                        type="number"
                        name="precio_con_iva"
                        value={formData.precio_con_iva.toFixed(2)}
                        onChange={handleChange}
                        className="w-full p-2 rounded bg-gray-700 text-white"
                        required
                    />
                </div>

                <div>
                    <label className="block text-white mb-2">Precio Minorista</label>
                    <input
                        type="number"
                        name="precio_minorista"
                        value={formData.precio_minorista.toFixed(2)}
                        onChange={handleChange}
                        className="w-full p-2 rounded bg-gray-700 text-white"
                        required
                    />
                </div>

                <div>
                    <label className="block text-white mb-2">Precio Mayorista</label>
                    <input
                        type="number"
                        name="precio_mayorista"
                        value={formData.precio_mayorista.toFixed(2)}
                        onChange={handleChange}
                        className="w-full p-2 rounded bg-gray-700 text-white"
                        required
                    />
                </div>

                <div>
                    <label className="block text-white mb-2">Precio Venta Minimo</label>
                    <input
                        type="number"
                        name="precio_venta_minimo"
                        value={formData.precio_venta_minimo.toFixed(2)}
                        onChange={handleChange}
                        className="w-full p-2 rounded bg-gray-700 text-white"
                        required
                    />
                </div>
                <div className="col-span-1 md:col-span-2">
                    <button
                        type="submit"
                        className="bg-blue-500 hover:bg-blue-700 text-white font-bold py-2 px-4 rounded w-full mt-4"
                    >
                        Guardar
                    </button>
                </div>
            </form>
        </div>
    );
};

export default EditProductForm;
